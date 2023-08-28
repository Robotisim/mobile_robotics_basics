#ifndef DEAD_RECKONING_H
#define DEAD_RECKONING_H

#include <Arduino.h>

extern float disp_r_wheel;
extern float disp_l_wheel;
extern int count_R_prev;
extern int count_L_prev;
extern float x;
extern float y;
extern float theta;
extern float meter_per_ticks;
extern float orientation_angle;
extern float disp_body;

extern int count_R;
extern int count_L;
extern const int channel_R;
extern const int channel_L;
extern int Right_motor_speed;
extern int Left_motor_speed;

void calculate_traveling();

#endif
