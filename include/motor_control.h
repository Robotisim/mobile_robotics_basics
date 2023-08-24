#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>


// Define pin connections & motor's states
#define ml_1 12
#define ml_2 13
#define mr_1 14
#define mr_2 27

// Define channels for LEDC functions
#define channel_l1 0
#define channel_l2 1
#define channel_r1 2
#define channel_r2 3

// Frequency for LEDC function
#define freq 5000

// Resolution for LEDC function
#define resolution 8

// Define a variable to hold the current speed
extern int currentSpeed; // Initial speed (adjust as needed)

void setupMotors();
void moveForward(int speed);
void moveBackward(int speed);
void turnRight(int speed);
void turnLeft(int speed);
void stopMotors();
void start_robot();
void handle_u_turn();

#endif