#include "robot_motion.hpp"

Robot::Robot()
    : motor_left(PWM_LEFT, MOTOR_LEFT_FW, MOTOR_LEFT_BW),
      motor_right(PWM_RIGHT, MOTOR_RIGHT_FW, MOTOR_RIGHT_BW) {
}

void Robot::moveForward() {
    motor_left.forward();
    motor_right.forward();
}

void Robot::stop() {
    motor_left.stop();
    motor_right.stop();
}

void Robot::turnLeft() {
    motor_left.stop();
    motor_right.forward();
}

void Robot::turnRight() {
    motor_left.forward();
    motor_right.stop();
}

void Robot::moveReverse() {
    motor_left.reverse();
    motor_right.reverse();
}
