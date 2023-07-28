#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "motor_control.h"
#include "ir_sensor.h"


void setup()
{
  setupSensor();
  setupMotors();
}

void loop()
{
  getData();
  delay(10);
}
