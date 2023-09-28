#include "motor_control.hpp"

MotorControl::MotorControl(int pwmPin,int forwardPin,int backwardPin)
: pwmPin_(pwmPin) ,forwardPin_(forwardPin) ,reversePin_(backwardPin){
    char *addrStr = NULL;
    char *portStr = NULL;
    pi = pigpio_start(addrStr, portStr);
    if(pi <0){
        std::cerr << "Failed to connect to PIGPIO Daemon." << std::endl;
        exit(EXIT_FAILURE);
    }

    initPins();
}

void MotorControl::initPins(){
        // Pin Functionality
    set_mode(pi,pwmPin_,PI_OUTPUT);
    set_mode(pi,forwardPin_,PI_OUTPUT);
    set_mode(pi,reversePin_,PI_OUTPUT);

    // Set Initialization
    gpio_write(pi,forwardPin_,0);
    gpio_write(pi,reversePin_,0);
}

MotorControl::~MotorControl(){
    pigpio_stop(pi);
}

void MotorControl::forward(){
    gpio_write(pi,forwardPin_,1);
    gpio_write(pi,reversePin_,0);
    set_PWM_dutycycle(pi,pwmPin_,150);

}
void MotorControl::stop(){
    gpio_write(pi,forwardPin_,0);
    gpio_write(pi,reversePin_,0);
    set_PWM_dutycycle(pi,pwmPin_,0);
}
void MotorControl::reverse(){
    gpio_write(pi,reversePin_,1);
    gpio_write(pi,forwardPin_,0);
    set_PWM_dutycycle(pi,pwmPin_,150);

}