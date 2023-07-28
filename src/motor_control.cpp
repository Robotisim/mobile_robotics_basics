#include "motor_control.h"



void setupMotors() {
  // Set the motor control pins to outputs
  pinMode(ml_1, OUTPUT);
  pinMode(ml_2, OUTPUT);
  pinMode(mr_1, OUTPUT);
  pinMode(mr_2, OUTPUT);

  // Setup LEDC
  ledcSetup(channel_l1, freq, resolution);
  ledcSetup(channel_l2, freq, resolution);
  ledcSetup(channel_r1, freq, resolution);
  ledcSetup(channel_r2, freq, resolution);

  // Attach the channels to the GPIOs
  ledcAttachPin(ml_1, channel_l1);
  ledcAttachPin(ml_2, channel_l2);
  ledcAttachPin(mr_1, channel_r1);
  ledcAttachPin(mr_2, channel_r2);

  Serial.begin(115200);
  Serial.println("Motors Starting");
}

void moveForward(int speed)
{
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_l2, speed);
  ledcWrite(channel_r2, speed);
}

void moveBackward(int speed)
{
  ledcWrite(channel_l1, speed);
  ledcWrite(channel_r1, speed);
  ledcWrite(channel_l2, 0);
  ledcWrite(channel_r2, 0);
}

void turnRight()
{
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_l2, 255);
  ledcWrite(channel_r2, 0);
}

void turnLeft()
{
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_l2, 0);
  ledcWrite(channel_r2, 255);
}

void stopMotors()
{
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_l2, 0);
  ledcWrite(channel_r2, 0);
}
