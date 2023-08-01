#include "motor_control.h"
#include "pi_controller.h"


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

void turnRight(int speed)
{
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_l2, speed);
  ledcWrite(channel_r2, 0);
}

void turnLeft(int speed)
{
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_l2, 0);
  ledcWrite(channel_r2, speed);
}

void stopMotors()
{
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_l2, 0);
  ledcWrite(channel_r2, 0);
}

// function to enable the motors of robot
void start_robot()
{
  digitalWrite(ml_1, HIGH); // Forward direction configuration
  digitalWrite(mr_1, HIGH);
}

void handle_u_turn()
{
// Make left turn until it detects a straight path
      do
      {
        moveBackward(200);
        delay(200);
        if (random(0, 2) == 0)
        {
          turnLeft(180);
        }
        else
        {
          turnRight(180);
        }
        read_sensor_values();

      } while (error != 0);
}