#ifndef ENCODER_CONTROL_H
#define ENCODER_CONTROL_H

#include <Wire.h>

extern const float WHEEL_DIAMETER; // Declare WHEEL_DIAMETER as an external variable

void setupEncoder0();
void setupEncoder1();
void readEncoderAngle0();
void readEncoderAngle1();
void getEncoderSpeed0();
void getEncoderSpeed1();

#endif // ENCODER_CONTROL_H
