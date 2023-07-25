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
const int AS5600_ADDRESS_LEFT = 0x36;
const int AS5600_ADDRESS_RIGHT = 0x37; 

// Variables for left-side encoder readings
int previousEncoderValueLeft = 0;
int currentEncoderValueLeft = 0;

// Variables for right-side encoder readings
int previousEncoderValueRight = 0;
int currentEncoderValueRight = 0;

unsigned long previousTime = 0;

// Define wheel properties
const float WHEEL_DIAMETER = 10.0; // in cm
const float ENCODER_RESOLUTION = 4096.0; // 12-bit resolution
//const float PI = 3.14159;

// Variables to store previous encoder time and value
unsigned long previousTimeLeft = 0;
unsigned long previousTimeRight = 0;

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
  Serial.println("Motors Starting");

  // Use GPIO 4 as SDA and GPIO 5 as SCL for the first encoder
  Wire.begin(4, 5);
  Serial.println("Encoder Speed Calculation");

}
// Function to read the encoder value from the left AS5600 encoder
int readEncoderLeft() {
  Wire.beginTransmission(AS5600_ADDRESS_LEFT);
  Wire.write(0x0E); // Register address for angle value
  Wire.endTransmission();

  Wire.requestFrom(AS5600_ADDRESS_LEFT, 2);
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
  Wire.beginTransmission(AS5600_ADDRESS_RIGHT);
  Wire.write(0x0E); // Register address for angle value
  Wire.endTransmission();

  Wire.requestFrom(AS5600_ADDRESS_RIGHT, 2);
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



void loop() {
  // Full speed forward for 3 seconds
  Serial.println("Motors FORWARD");
  ledcWrite(channel_l1, 0);
  //ledcWrite(channel_r1, 0);
  ledcWrite(channel_l2, 180);
  //ledcWrite(channel_r2, 180);
  delay(20);

  // Read the current encoder value for the left encoder (GPIO 4 and GPIO 5)
  currentEncoderValueLeft = readEncoderLeft();

  // Delay to give some time before reading the second encoder
  delay(10);

  // Read the current encoder value for the right encoder (GPIO 21 and GPIO 22)
  currentEncoderValueRight = readEncoderRight();


  // Calculate the time elapsed since the last reading for left and right encoders
  unsigned long currentTime = millis();
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


  // Add a delay to control the update frequency (adjust as needed)
  delay(10);
}

