#include "MotorControl.h"
#include <SPI.h>
#include <Wire.h>

void setupMotors() {
  // Set the motor control pins to outputs
  pinMode(ml_1, OUTPUT);
  pinMode(ml_2, OUTPUT);
  pinMode(mr_1, OUTPUT);
  pinMode(mr_2, OUTPUT);

  // Setup LEDC
  ledcSetup(channel_l1, PWM_FREQ, resolution);
  ledcSetup(channel_l2, PWM_FREQ, resolution);
  ledcSetup(channel_r1, PWM_FREQ, resolution);
  ledcSetup(channel_r2, PWM_FREQ, resolution);

  // Attach the channels to the GPIOs
  ledcAttachPin(ml_1, channel_l1);
  ledcAttachPin(ml_2, channel_l2);
  ledcAttachPin(mr_1, channel_r1);
  ledcAttachPin(mr_2, channel_r2);

  Serial.begin(115200);
  Serial.println("Motors Starting");
}

void stopMotors() {
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_l2, 0);
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_r2, 0);
}

void moveForward() {
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_l2, 180);
  ledcWrite(channel_r2, 0);
}

void moveBackward() {
  ledcWrite(channel_l1, 180);
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_l2, 0);
  ledcWrite(channel_r2, 0);
}

void setPWM(int pwmValue) {
  ledcWrite(channel_l1, pwmValue);
  ledcWrite(channel_r1, pwmValue);
  ledcWrite(channel_l2, pwmValue);
  ledcWrite(channel_r2, pwmValue);
}
