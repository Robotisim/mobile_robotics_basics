#ifndef PI_CONTROLLER_H
#define PI_CONTROLLER_H

class PIController {
public:
    PIController(float kp, float ki);
    void setGains(float kp, float ki);
    float calculateControlSignal(float error);
    
private:
    float Kp;
    float Ki;
    float integral;
    float lastError;
};

#endif
