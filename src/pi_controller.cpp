#include "pi_controller.h"

PIController::PIController(float kp, float ki) : Kp(kp), Ki(ki), integral(0), lastError(0) {}

void PIController::setGains(float kp, float ki) {
    Kp = kp;
    Ki = ki;
}

float PIController::calculateControlSignal(float error) {
    integral += error;
    if (integral > 100) {
        integral = 100;
    } else if (integral < -100) {
        integral = -100;
    }
    
    float controlSignal = Kp * error + Ki * integral;
    lastError = error;
    return controlSignal;
}
