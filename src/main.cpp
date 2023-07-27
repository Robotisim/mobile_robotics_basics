#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>
#include "MotorControl.h"
#include "EncoderControl.h"
#include "AS5600.h"

unsigned long startTime = 0;
unsigned long motorDuration = 1000; // 2 seconds for each direction

// Define wheel properties
const float WHEEL_DIAMETER = 3.28; // in cm (32.8 mm)

void setup()
{
  setupMotors();
  Serial.begin(115200);
  Wire.begin();
  setupEncoder0();
  setupEncoder1();
  delay(1000);
  startTime = millis();
}

void loop()
{
  // Check if the motor duration has elapsed
  unsigned long currentTime = millis();

  // Calculate the elapsed time since the start
  unsigned long elapsedTime = currentTime - startTime;

  // Full speed forward for the first 2 seconds
  if (elapsedTime <= motorDuration)
  {
    moveForward(); // Move forward
  }
  // Then full speed backward for the next 2 seconds
  // else if (elapsedTime > motorDuration && elapsedTime <= motorDuration * 2)
  // {
  //   moveBackward(); // Move backward
  // }
  // // Reset the start time after 4 seconds (2 seconds forward + 2 seconds backward)
  else if (elapsedTime > motorDuration)
  {
    currentTime = elapsedTime;
    stopMotors();
    Serial.println("Motors stopped ");
  }

  readEncoderAngle0();
  getEncoderSpeed0();
  readEncoderAngle1();
  getEncoderSpeed1();

  if (elapsedTime > motorDuration * 1.2)
  {
    delay(100000);
  }
}
