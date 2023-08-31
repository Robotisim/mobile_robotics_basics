#ifndef ENCODER_CONTROL_H
#define ENCODER_CONTROL_H

#include <Wire.h>

void setupEncoder0();
void setupEncoder1();
int cummulativePos0();
int cummulativePos1();

#endif // ENCODER_CONTROL_H

