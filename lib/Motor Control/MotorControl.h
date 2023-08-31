#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

// Define pin connections & motor's states
#define ml_1 14
#define ml_2 27
#define mr_1 25
#define mr_2 26

// Define channels for LEDC functions
#define channel_l1 0
#define channel_l2 1
#define channel_r1 2
#define channel_r2 3

// Frequency for LEDC function
#define PWM_FREQ 5000

// Resolution for LEDC function
#define resolution 8

// Function prototypes
void setupMotors();
void stopMotors();
void moveForward(int PWM);
void moveBackward(int PWM);
void motorLeftStop();
void motorRightStop();
void moveRightF(int PWM);
void moveLeftF(int PWM);
void moveRightB(int PWM);
void moveLeftB(int PWM);
void processData(String data);


#endif // MOTOR_CONTROL_H
