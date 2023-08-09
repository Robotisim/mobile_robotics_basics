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

  readEncoderAngle0();
  getEncoderSpeed0();
  readEncoderAngle1();
  getEncoderSpeed1();
  // moveForward(180);
  // moveBackward(180);
}
