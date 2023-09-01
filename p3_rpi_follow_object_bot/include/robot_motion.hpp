#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "motor_control.hpp"

class Robot {
public:
    Robot();
    void moveForward();
    void stop();
    void turnLeft();
    void turnRight();
    void moveReverse();

private:
    MotorControl motor_left;
    MotorControl motor_right;
};

#endif
