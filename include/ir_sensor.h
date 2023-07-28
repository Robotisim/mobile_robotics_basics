#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

//**********5 Channel IR Sensor Connection**********//
#define ir1 34
#define ir2 35
#define ir3 32
#define ir4 33
#define ir5 15

void setupSensor();
void getData();


#endif
