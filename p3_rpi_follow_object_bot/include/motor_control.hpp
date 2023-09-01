#ifndef MOTOR_CONTROL_HPP
#define MOTOR_CONTROL_HPP


#include <pigpiod_if2.h>
#include <iostream>

class MotorControl{
public:
    MotorControl();
    ~MotorControl();
    void forward();
    void stop();


private:
    int pi;
    const int PWM_LEFT =19;
    const int MOTOR_LEFT_FW =6;
    const int MOTOR_LEFT_BW =26;
};

#endif