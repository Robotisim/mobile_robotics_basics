#ifndef MOTOR_CONTROL_HPP
#define MOTOR_CONTROL_HPP


#include <pigpiod_if2.h>
#include <iostream>

const int PWM_LEFT =19;
const int MOTOR_LEFT_FW =6;
const int MOTOR_LEFT_BW =26;

const int PWM_RIGHT =13;
const int MOTOR_RIGHT_FW =11;
const int MOTOR_RIGHT_BW =5;

class MotorControl{
public:
    MotorControl(int pwmPin,int forwardPin,int backwardPin);
    ~MotorControl();
    void forward();
    void stop();
    void reverse();


private:
    int pi;
    int pwmPin_,forwardPin_,reversePin_;

    void initPins();
};

#endif