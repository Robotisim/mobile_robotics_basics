#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>
#include "AS5600.h"

// Define pin connections & motor's states
#define ml_1 27
#define ml_2 14
#define mr_1 26
#define mr_2 25

// Define channels for LEDC functions
#define channel_l1 0
#define channel_l2 1
#define channel_r1 2
#define channel_r2 3

// Frequency for LEDC function
#define freq 5000

// Resolution for LEDC function
#define resolution 8

// Define I2C address for AS5600 encoder
const int AS5600_ADDRESS = 0x36;

/*// Variables for left-side encoder readings
int previousEncoderValueLeft = 0;
int currentEncoderValueLeft = 0;

// Variables for right-side encoder readings
int previousEncoderValueRight = 0;
int currentEncoderValueRight = 0;*/


unsigned long previousTime = 0;
unsigned long startTime = 0;
unsigned long motorDuration = 10000; // 10 seconds

// Define wheel properties
const float WHEEL_DIAMETER = 10.0; // in cm
const float ENCODER_RESOLUTION = 4096.0; // 12-bit resolution
//const float PI = 3.14159;

/*// Variables to store previous encoder time and value
unsigned long previousTimeLeft = 0;
unsigned long previousTimeRight = 0;*/



//Magnetic sensor things
int magnetStatus = 0; //value of the status register (MD, ML, MH)

int lowbyte; //raw angle 7:0
word highbyte; //raw angle 7:0 and 11:8
int rawAngle; //final raw angle 
float degAngle; //raw angle in degrees (360/4096 * [value between 0-4095])

int quadrantNumber, previousquadrantNumber; //quadrant IDs
float numberofTurns = 0; //number of turns
float correctedAngle = 0; //tared angle - based on the startup value
float startAngle = 0; //starting angle
float totalAngle = 0; //total absolute angular displacement
float previoustotalAngle = 0; //for the display printing

void ReadRawAngle()
{ 
  //7:0 - bits
  Wire.beginTransmission(0x36); //connect to the sensor
  Wire.write(0x0D); //figure 21 - register map: Raw angle (7:0)
  Wire.endTransmission(); //end transmission
  Wire.requestFrom(0x36, 1); //request from the sensor
  
  while(Wire.available() == 0); //wait until it becomes available 
  lowbyte = Wire.read(); //Reading the data after the request
 
  //11:8 - 4 bits
  Wire.beginTransmission(0x36);
  Wire.write(0x0C); //figure 21 - register map: Raw angle (11:8)
  Wire.endTransmission();
  Wire.requestFrom(0x36, 1);
  
  while(Wire.available() == 0);  
  highbyte = Wire.read();
  
  //4 bits have to be shifted to its proper place as we want to build a 12-bit number
  highbyte = highbyte << 8; //shifting to left
  //What is happening here is the following: The variable is being shifted by 8 bits to the left:
  //Initial value: 00000000|00001111 (word = 16 bits or 2 bytes)
  //Left shifting by eight bits: 00001111|00000000 so, the high byte is filled in
  
  //Finally, we combine (bitwise OR) the two numbers:
  //High: 00001111|00000000
  //Low:  00000000|00001111
  //      -----------------
  //H|L:  00001111|00001111
  rawAngle = highbyte | lowbyte; //int is 16 bits (as well as the word)

  //We need to calculate the angle:
  //12 bit -> 4096 different levels: 360° is divided into 4096 equal parts:
  //360/4096 = 0.087890625
  //Multiply the output of the encoder with 0.087890625
  degAngle = rawAngle * 0.087890625; 
  
  Serial.print("Deg angle: ");
  Serial.println(degAngle, 2); //absolute position of the encoder within the 0-360 circle
  
}

void correctAngle()
{
  //recalculate angle
  correctedAngle = degAngle - startAngle; //this tares the position

  if(correctedAngle < 0) //if the calculated angle is negative, we need to "normalize" it
  {
  correctedAngle = correctedAngle + 360; //correction for negative numbers (i.e. -15 becomes +345)
  }
  else
  {
    //do nothing
  }
  //Serial.print("Corrected angle: ");
  //Serial.println(correctedAngle, 2); //print the corrected/tared angle  
}

void checkQuadrant()
{
  /*
  //Quadrants:
  4  |  1
  ---|---
  3  |  2
  */

  //Quadrant 1
  if(correctedAngle >= 0 && correctedAngle <=90)
  {
    quadrantNumber = 1;
  }

  //Quadrant 2
  if(correctedAngle > 90 && correctedAngle <=180)
  {
    quadrantNumber = 2;
  }

  //Quadrant 3
  if(correctedAngle > 180 && correctedAngle <=270)
  {
    quadrantNumber = 3;
  }

  //Quadrant 4
  if(correctedAngle > 270 && correctedAngle <360)
  {
    quadrantNumber = 4;
  }
  //Serial.print("Quadrant: ");
  //Serial.println(quadrantNumber); //print our position "quadrant-wise"

  if(quadrantNumber != previousquadrantNumber) //if we changed quadrant
  {
    if(quadrantNumber == 1 && previousquadrantNumber == 4)
    {
      numberofTurns++; // 4 --> 1 transition: CW rotation
    }

    if(quadrantNumber == 4 && previousquadrantNumber == 1)
    {
      numberofTurns--; // 1 --> 4 transition: CCW rotation
    }
    //this could be done between every quadrants so one can count every 1/4th of transition

    previousquadrantNumber = quadrantNumber;  //update to the current quadrant
  
  }  
  Serial.print("Turns: ");
  Serial.println(numberofTurns,0); //number of turns in absolute terms (can be negative which indicates CCW turns)  

  //after we have the corrected angle and the turns, we can calculate the total absolute position
  totalAngle = (numberofTurns*360) + correctedAngle; //number of turns (+/-) plus the actual angle within the 0-360 range
  Serial.print("Total angle: ");
  Serial.println(totalAngle, 2); //absolute position of the motor expressed in degree angles, 2 digits
}

void checkMagnetPresence()
{  
  //This function runs in the setup() and it locks the MCU until the magnet is not positioned properly

  while((magnetStatus & 32) != 32) //while the magnet is not adjusted to the proper distance - 32: MD = 1
  {
    magnetStatus = 0; //reset reading

    Wire.beginTransmission(0x36); //connect to the sensor
    Wire.write(0x0B); //figure 21 - register map: Status: MD ML MH
    Wire.endTransmission(); //end transmission
    Wire.requestFrom(0x36, 1); //request from the sensor

    while(Wire.available() == 0); //wait until it becomes available 
    magnetStatus = Wire.read(); //Reading the data after the request

    //Serial.print("Magnet status: ");
    //Serial.println(magnetStatus, BIN); //print it in binary so you can compare it to the table (fig 21)      
  }      
  
  //Status register output: 0 0 MD ML MH 0 0 0  
  //MH: Too strong magnet - 100111 - DEC: 39 
  //ML: Too weak magnet - 10111 - DEC: 23     
  //MD: OK magnet - 110111 - DEC: 55

  //Serial.println("Magnet found!");
  //delay(1000);  
}


void setup() {
  // Set the motor control pins to outputs
  pinMode(ml_1, OUTPUT);
  pinMode(ml_2, OUTPUT);
  pinMode(mr_1, OUTPUT);
  pinMode(mr_2, OUTPUT);

  // Setup LEDC
  ledcSetup(channel_l1, freq, resolution);
  ledcSetup(channel_l2, freq, resolution);
  ledcSetup(channel_r1, freq, resolution);
  ledcSetup(channel_r2, freq, resolution);

  // Attach the channels to the GPIOs
  ledcAttachPin(ml_1, channel_l1);
  ledcAttachPin(ml_2, channel_l2);
  ledcAttachPin(mr_1, channel_r1);
  ledcAttachPin(mr_2, channel_r2);
  
  Serial.begin(115200);
  Wire.begin(); //start i2C  
	Wire.setClock(800000L); //fast clock
  Serial.println("Motors Starting");
  
  checkMagnetPresence(); //check the magnet (blocks until magnet is found)

  ReadRawAngle(); //make a reading so the degAngle gets updated
  startAngle = degAngle; //update startAngle with degAngle - for taring

  // Use GPIO 4 as SDA and GPIO 5 as SCL for the first encoder
  //Wire.begin(4, 5);
  // Use GPIO 21 as SDA and GPIO 22 as SCL for the second encoder
  Wire.begin(21, 22);
  Serial.println("Encoder Speed Calculation");

  // Record the start time
 // startTime = millis();
}
/*
// Function to read the encoder value from the left AS5600 encoder
int readEncoderLeft() {
  Wire.beginTransmission(AS5600_ADDRESS);
  Wire.write(0x0E); // Register address for angle value
  Wire.endTransmission();

  Wire.requestFrom(AS5600_ADDRESS, 2);
  if (Wire.available() >= 2) {
    int angleValueLeft = (Wire.read() << 8) | Wire.read();
    Serial.print("Left Encoder Angle Value: ");
    Serial.println(angleValueLeft);
    return angleValueLeft;
  }
  return 0;
}

// Function to read the encoder value from the right AS5600 encoder
int readEncoderRight() {
  Wire.beginTransmission(AS5600_ADDRESS);
  Wire.write(0x0E); // Register address for angle value
  Wire.endTransmission();

  Wire.requestFrom(AS5600_ADDRESS, 2);
  if (Wire.available() >= 2) {
    int angleValueRight = (Wire.read() << 8) | Wire.read();
    Serial.print("Right Encoder Angle Value: ");
    Serial.println(angleValueRight);
    return angleValueRight;
  }
  return 0;
}

// Helper function to calculate the delta angle considering the circular nature of the encoder
int calculateDeltaAngle(int currentAngle, int previousAngle) {
  int deltaAngle = currentAngle - previousAngle;
  
  // Handle encoder value rollover from 4096 to 0
  if (deltaAngle < -2048) {
    deltaAngle += 4096;
  }
  // Handle encoder value rollover from 0 to 4096
  else if (deltaAngle > 2048) {
    deltaAngle -= 4096;
  }
  
  return deltaAngle;
}




void stopMotors() {
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_l2, 0);
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_r2, 0);
}
*/
void loop() {

  ReadRawAngle(); //ask the value from the sensor
  correctAngle(); //tare the value
  checkQuadrant(); //check quadrant, check rotations, check absolute angular position

/*
  // Check if the motor duration has elapsed
  unsigned long currentTime = millis();
  if (currentTime - startTime >= motorDuration) {
    stopMotors();
    Serial.println("Motors Stopped");
    while (true) {
      // Stay here indefinitely after stopping the motors
    }
  }
*/
  // Full speed forward
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_l2, 180);
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_r2, 0);
/*
  // Read the current encoder value for the left encoder (GPIO 4 and GPIO 5)
  currentEncoderValueLeft = readEncoderLeft();

  // Delay to give some time before reading the second encoder
  delay(10);

  // Read the current encoder value for the right encoder (GPIO 21 and GPIO 22)
  currentEncoderValueRight = readEncoderRight();


  // Calculate the time elapsed since the last reading for left and right encoders
  unsigned long deltaTimeLeft = currentTime - previousTimeLeft;
  unsigned long deltaTimeRight = currentTime - previousTimeRight;

  // Calculate the change in encoder values for left and right encoders (using the helper function)
  int deltaEncoderValueLeft = calculateDeltaAngle(currentEncoderValueLeft, previousEncoderValueLeft);
  int deltaEncoderValueRight = calculateDeltaAngle(currentEncoderValueRight, previousEncoderValueRight);

  // Calculate wheel rotation angles in degrees for left and right encoders
  float wheelRotationAngleLeft = (float(deltaEncoderValueLeft) / ENCODER_RESOLUTION) * 360.0;
  float wheelRotationAngleRight = (float(deltaEncoderValueRight) / ENCODER_RESOLUTION) * 360.0;

  // Calculate wheel speeds in RPM for left and right encoders
  float wheelSpeedRPMLeft = (wheelRotationAngleLeft / deltaTimeLeft) * (60000.0 / 360.0);
  float wheelSpeedRPMRight = (wheelRotationAngleRight / deltaTimeRight) * (60000.0 / 360.0);

  // Print the calculated speeds
  Serial.print("Left Wheel Speed: ");
  Serial.print(wheelSpeedRPMLeft);
  Serial.println(" RPM");

  Serial.print("Right Wheel Speed: ");
  Serial.print(wheelSpeedRPMRight);
  Serial.println(" RPM");

  if (deltaEncoderValueLeft > 0 and deltaEncoderValueRight > 0){
    Serial.println("Moving forward.");
  }
  else if (deltaEncoderValueLeft < 0 and deltaEncoderValueRight < 0){
    Serial.println("Moving backward.");
  }

  // Add your comparison logic here to determine the robot's movement direction
  // For example:
  if (wheelSpeedRPMLeft > wheelSpeedRPMRight) {
    // The robot turned right
    Serial.println("Robot turned right");
  } else if (wheelSpeedRPMLeft < wheelSpeedRPMRight) {
    // The robot turned left
    Serial.println("Robot turned left");
  } else {
    // The robot is moving straight
    Serial.println("Robot is moving straight");
  }

  // Update previous values for the next iteration
  previousEncoderValueLeft = currentEncoderValueLeft;
  previousEncoderValueRight = currentEncoderValueRight;
  previousTimeLeft = currentTime;
  previousTimeRight = currentTime;
*/
  // Add a delay to control the update frequency (adjust as needed)
  delay(100);
}
