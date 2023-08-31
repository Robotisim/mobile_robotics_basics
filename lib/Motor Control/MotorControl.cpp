#include "MotorControl.h"
#include <SPI.h>
#include <Wire.h>
#include  "wifi_data_processing.h"

void setupMotors() {
  // Set the motor control pins to outputs
  pinMode(ml_1, OUTPUT);
  pinMode(ml_2, OUTPUT);
  pinMode(mr_1, OUTPUT);
  pinMode(mr_2, OUTPUT);

  // Setup LEDC
  ledcSetup(channel_l1, PWM_FREQ, resolution);
  ledcSetup(channel_l2, PWM_FREQ, resolution);
  ledcSetup(channel_r1, PWM_FREQ, resolution);
  ledcSetup(channel_r2, PWM_FREQ, resolution);

  // Attach the channels to the GPIOs
  ledcAttachPin(ml_1, channel_l1);
  ledcAttachPin(ml_2, channel_l2);
  ledcAttachPin(mr_1, channel_r1);
  ledcAttachPin(mr_2, channel_r2);

  Serial.begin(115200);
  Serial.println("Motors Starting");
}

void stopMotors() {
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_l2, 0);
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_r2, 0);
}

void moveForward(int PWM) {
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_l2, PWM);
  ledcWrite(channel_r2, PWM);
}

void moveBackward(int PWM) {
  ledcWrite(channel_l1, PWM);
  ledcWrite(channel_r1, PWM);
  ledcWrite(channel_l2, 0);
  ledcWrite(channel_r2, 0);
}


void motorLeftStop(){
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_l2, 0);
}

void motorRightStop(){
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_r2, 0);
}

void moveRightF(int PWM){
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_r2, PWM);
}

void moveLeftF(int PWM){
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_l2, PWM);
}

void moveRightB(int PWM){
  ledcWrite(channel_r1, PWM);
  ledcWrite(channel_r2, 0);
}

void moveLeftB(int PWM){
  ledcWrite(channel_l1, PWM);
  ledcWrite(channel_l2, 0);
}

void processData(String data)
{
  // Convert the received data to lowercase for case-insensitive comparison
  data.toLowerCase();

  // Check if the data contains a comma (indicating it's a coordinate)
  int commaIndex = data.indexOf(",");
  if (commaIndex != -1)
  {
    // Process the received coordinate data
    float xCoordinate = data.substring(0, commaIndex).toFloat();
    float yCoordinate = data.substring(commaIndex + 1).toFloat();
    
    // Call a function to process the coordinates (replace with your actual function)
    processCoordinates(xCoordinate, yCoordinate);
  }
  else
  {
    // Process the received string command
    if (data == "forward")
    {
      moveForward(255); // Set the speed as needed (0 to 255)
    }
    else if (data == "backward")
    {
      moveBackward(255); // Set the speed as needed (0 to 255)
    }
    else if (data == "right")
    {
      motorRightStop();
      moveLeftF(255); // Set the speed as needed (0 to 255)
    }
    else if (data == "left")
    {
      motorLeftStop();
      moveRightF(255); // Set the speed as needed (0 to 255)
    }
    else if (data == "stop")
    {
      stopMotors();
    }
  }
}
