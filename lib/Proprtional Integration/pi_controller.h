#ifndef PI_CONTROL_H
#define PI_CONTROL_H

#include <Arduino.h>

// Declare the external variables
extern int sensor[5];
extern float error;
extern int Right_motor_speed;
extern int Left_motor_speed;
extern float P;
extern float PI_value;

// Function declarations
void read_sensor_values();
void calculate_pid();
void motor_control();

#endif // PI_CONTROL_H
