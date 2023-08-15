#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>
#include "MotorControl.h"
#include "EncoderControl.h"
#include "AS5600.h"


void setup()
{
  setupMotors();
  Serial.begin(115200);
  Wire.begin();
  setupEncoder0();
  setupEncoder1();
  delay(1000);
}

void loop()
{
  if (getEncoderRevolutions0() > -2 )
  {
    moveRightF(150);
  }
  else
  {
    motorRightStop();
  }

  if (getEncoderRevolutions1() < 2)
  {
    moveLeftF(180);
  }
  else
  {
    motorLeftStop();
  }

}

