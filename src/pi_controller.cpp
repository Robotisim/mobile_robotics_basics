#include "pi_controller.h"
#include "motor_control.h"

#define ir1 35
#define ir2 32
#define ir3 33
#define ir4 25
#define ir5 26

// Initial Values of Sensors

int sensor[5] = {0, 0, 0, 0, 0};
// Initial Speed of Motor
int Right_motor_speed = 100; // Motor Base speeds
int Left_motor_speed = 100;

// PI Constants
float Kp = 25;
float Ki = 0.4;

float error = 0, P = 0, I = 0, PI_value = 0;
float previous_error = 0;
float I_limit = 100; // Set an appropriate limit for the integral term

void read_sensor_values()
{

  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);

  sensor[0] = !digitalRead(ir1);
  sensor[1] = !digitalRead(ir2);
  sensor[2] = !digitalRead(ir3);
  sensor[3] = !digitalRead(ir4);
  sensor[4] = !digitalRead(ir5);

  // Serial.print(sensor[0]);
  // Serial.print("\t");
  // Serial.print(sensor[1]);
  // Serial.print("\t");
  // Serial.print(sensor[2]);
  // Serial.print("\t");
  // Serial.print(sensor[3]);
  // Serial.print("\t");
  // Serial.print(sensor[4]);
  // Serial.print("\t");
  /*
  The sensor values are converted to error values.
  If on black line will output 1   (readings are actually inverted if you look at digital read function)
  Any other value will output 0.
  In this code we are actually using the black line as the error and white as the reference.
  Have to follow the black line.
  if black line on left side increase right motors speed and decrease left motor speed to turn left quickly
  or slowly will depend on the error value.
  ##########IMPORTANT NOTE################
  If your code is not working then change sign of error value.
  Check motor connections.
  Check what your sensor outputs for black and white.
  */
  if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 0))
    error = -6;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0))
    error = -5;
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0))
    error = -4;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0))
    error = -3;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0))
    error = -2;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0))
    error = -1;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 0) && (sensor[4] == 0))
    error = 0;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 0))
    error = 1;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 0))
    error = 2;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1) && (sensor[4] == 1))
    error = 3;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 1))
    error = 4;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))
    error = 5;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1))
    error = 6;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0) && (sensor[4] == 0)) // Make U turn
    error = 102;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1) && (sensor[4] == 1)) // T juction skipping
    error = 0;
  else
    error = 103;
}

void calculate_pid()
{
  P = error;
  I = I + error;

  I = constrain(I, -I_limit, I_limit);
  PI_value = (Kp * P) + (Ki * I);
}

void motor_control()
{
  // Calculating the effective motor speed:
  int left_motor_speed = Left_motor_speed - PI_value;
  int right_motor_speed = Right_motor_speed + PI_value;

  // The motor speed should not exceed the max PWM value
  left_motor_speed = constrain(left_motor_speed, 90, 200);
  right_motor_speed = constrain(right_motor_speed, 90, 200);

  // Serial.print(PI_value);
  // Serial.print("\t");
  // Serial.print(left_motor_speed);
  // Serial.print("\t");
  // Serial.println(right_motor_speed);

  ledcWrite(channel_l2, left_motor_speed);
  ledcWrite(channel_r2, right_motor_speed);
}
