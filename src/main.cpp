#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>
#include "MotorControl.h"
#include "EncoderControl.h"
#include "AS5600.h"

AS5600L as5600; //  use default Wire

unsigned long startTime = 0;
unsigned long motorDuration = 1000; // 2 seconds for each direction


void setup()
{
  setupMotors();

  Serial.begin(115200);
  as5600.begin(21, 22);    //  ESP32
  as5600.setAddress(0x36); //  AS5600L has address

  as5600.setDirection(AS5600_CLOCK_WISE); //  default, just be explicit.
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
  // static uint32_t lastTime = 0;
  // as5600.getCumulativePosition();

  // int angle = as5600.readAngle();
  // Serial.print("Resolution: ");
  // Serial.println(angle);
  // Serial.print("Degrees: ");
  // Serial.println(as5600.rawAngle() * AS5600_RAW_TO_DEGREES);
  //  update every 100 ms
  // if (millis() - lastTime >= 100)
  //  {
  //    lastTime = millis();
  //    Serial.print("Position: ");
  //    Serial.println(as5600.getCumulativePosition());
  //    Serial.print("Revolutions: ");
  //    Serial.println(as5600.getRevolutions());
  //  }
  Serial.print("RPM: ");
  Serial.println(as5600.getAngularSpeed(AS5600_MODE_RPM));
  //delay(300); // You can adjust this delay to control the update frequency, but don't make it too short.
  if (elapsedTime > motorDuration * 2)
  {
    delay(100000);
  }
  
}
