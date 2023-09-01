#include "motor_control.hpp"
#include <iostream>

// Default constructor
MotorControl::MotorControl() {
    char *addrStr = nullptr;
    char *portStr = nullptr;
    pi = pigpio_start(addrStr, portStr);

    if (pi < 0) {
        std::cerr << "Failed to connect to PIGPIO Daemon." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Assign default pin values
    pwmPin = PWM_LEFT;
    forwardPin = MOTOR_LEFT_FW;
    backwardPin = MOTOR_LEFT_BW;

    // Initialize the pins
    initPins();
}

// Parameterized constructor
MotorControl::MotorControl(int pwmPin, int forwardPin, int backwardPin)
    : pwmPin(pwmPin), forwardPin(forwardPin), backwardPin(backwardPin) {

    char *addrStr = nullptr;
    char *portStr = nullptr;
    pi = pigpio_start(addrStr, portStr);

    if (pi < 0) {
        std::cerr << "Failed to connect to PIGPIO Daemon." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Initialize the pins
    initPins();
}

// Destructor
MotorControl::~MotorControl() {
    pigpio_stop(pi);
}

void MotorControl::initPins() {
    // Set pin modes
    set_mode(pi, pwmPin, PI_OUTPUT);
    set_mode(pi, forwardPin, PI_OUTPUT);
    set_mode(pi, backwardPin, PI_OUTPUT);

    // Initialize motor to stop
    gpio_write(pi, forwardPin, 0);
    gpio_write(pi, backwardPin, 0);
}

void MotorControl::forward() {
    std::cout << "Moving Forward" << std::endl;
    gpio_write(pi, forwardPin, 1);
    gpio_write(pi, backwardPin, 0);
    set_PWM_dutycycle(pi, pwmPin, 150);
}

void MotorControl::stop() {
    std::cout << "Stopping" << std::endl;
    gpio_write(pi, forwardPin, 0);
    gpio_write(pi, backwardPin, 0);
    set_PWM_dutycycle(pi, pwmPin, 0);
}

void MotorControl::reverse() {
    std::cout << "Moving in Reverse" << std::endl;
    gpio_write(pi, forwardPin, 0);
    gpio_write(pi, backwardPin, 1);
    set_PWM_dutycycle(pi, pwmPin, 150);
}

// Implement other methods like right() and left() similarly
