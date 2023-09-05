#ifndef MOTOR_CONTROL_HPP
#define MOTOR_CONTROL_HPP

#include <pigpiod_if2.h>
#include <iostream>

const int PWM_LEFT = 19;
const int MOTOR_LEFT_FW = 6;
const int MOTOR_LEFT_BW = 26;

const int PWM_RIGHT = 13; // Example value, replace with actual
const int MOTOR_RIGHT_FW = 11; // Example value, replace with actual
const int MOTOR_RIGHT_BW = 5; // Example value, replace with actual

class MotorControl {
public:
    MotorControl();
    MotorControl(int pwmPin, int forwardPin, int backwardPin);
    ~MotorControl();
    void forward();
    void stop();
    void reverse();

private:
    void initPins();  // Add this line
    int pi;
    int pwmPin, forwardPin, backwardPin;
};

#endif
