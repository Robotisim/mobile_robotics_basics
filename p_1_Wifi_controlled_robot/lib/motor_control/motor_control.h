#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

// Pin Definitions
#define motor_right_b 14
#define motor_right_a 27
#define motor_left_a 26
#define motor_left_b 25

// Channels
#define pwm_channel_mr_a 0
#define pwm_channel_mr_b 1
#define pwm_channel_ml_a 2
#define pwm_channel_ml_b 3

// Functions
void forward(int speed);
void stop();
void left(int speed);
void right(int speed);
void reverse(int speed);
void motor_setup();
#endif
