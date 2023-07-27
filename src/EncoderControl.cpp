#include "EncoderControl.h"
#include <Wire.h>

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
