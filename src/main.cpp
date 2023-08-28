#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>
#include "MotorControl.h"
#include "EncoderControl.h"
#include "AS5600.h"
#include "dead_Reckoning.h"

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
  calculate_traveling();
  Serial.print("X: " );
  Serial.print(x);
  Serial.print(" | Y: ");
  Serial.println(y);
  delay(1000);
}

