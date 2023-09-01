#include "motor_control.hpp"

MotorControl::MotorControl(){
    char *addrStr = NULL;
    char *portStr = NULL;
    pi = pigpio_start(addrStr, portStr);
    if(pi <0){
        std::cerr << "Failed to connect to PIGPIO Daemon." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Pin Functionality
    set_mode(pi,PWM_LEFT,PI_OUTPUT);
    set_mode(pi,MOTOR_LEFT_FW,PI_OUTPUT);
    set_mode(pi,MOTOR_LEFT_BW,PI_OUTPUT);

    // Set Initialization
    gpio_write(pi,MOTOR_LEFT_FW,0);
    gpio_write(pi,MOTOR_LEFT_BW,0);
}


MotorControl::~MotorControl(){
    pigpio_stop(pi);
}

void MotorControl::forward(){
    std::cout << "Forward" << std::endl;
    gpio_write(pi,MOTOR_LEFT_FW,1);
    set_PWM_dutycycle(pi,PWM_LEFT,150);
    time_sleep(3);
}
void MotorControl::stop(){
    std::cout << "Stopping" << std::endl;
    gpio_write(pi,MOTOR_LEFT_FW,0);
    set_PWM_dutycycle(pi,PWM_LEFT,0);
    time_sleep(3);
}