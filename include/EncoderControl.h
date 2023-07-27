#ifndef ENCODER_CONTROL_H
#define ENCODER_CONTROL_H

#include <Arduino.h>

// Define I2C address for AS5600 encoder
const int AS5600_ADDRESS = 0x36;

// Function prototypes
int readEncoderLeft();
int calculateDeltaAngle(int currentAngle, int previousAngle);

#endif // ENCODER_CONTROL_H
