#include "robot_motion.hpp"

Robot_motion::Robot_motion()
    : motor_left(PWM_LEFT, MOTOR_LEFT_FW, MOTOR_LEFT_BW),
      motor_right(PWM_RIGHT, MOTOR_RIGHT_FW, MOTOR_RIGHT_BW) {
}

void Robot_motion::moveForward() {
    std::cout<<"Forward Motion "<<std::endl;
    motor_left.forward();
    motor_right.forward();
}

void Robot_motion::stop() {
    std::cout<<"Stoppign robot "<<std::endl;
    motor_left.stop();
    motor_right.stop();
}

void Robot_motion::turnLeft() {
    std::cout<<"Turning Left "<<std::endl;
    motor_left.stop();
    motor_right.forward();
}

void Robot_motion::turnRight() {
    std::cout<<"Turning Right "<<std::endl;
    motor_left.forward();
    motor_right.stop();
}

void Robot_motion::moveReverse() {
    std::cout<<"Reverse Motion "<<std::endl;
    motor_left.reverse();
    motor_right.reverse();
}
