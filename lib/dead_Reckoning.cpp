//  http://www-personal.umich.edu/~johannb/position.htm book link

#include <Arduino.h>
#include "dead_Reckoning.h"
#include "EncoderControl.h"

// Fixed values
#define WHEEL_DIAMETER 0.0335
#define PULSES_PER_REVOLUTION 4096.0
#define AXLE_LENGTH 0.067
#define PI 3.1415926535897932384626433832795

// New Variables
float disp_r_wheel = 0;
float disp_l_wheel = 0;
int count_R_prev = 0;
int count_L_prev = 0;
float x = 0;
float y = 0;
float theta = 0;
float meter_per_ticks = PI * WHEEL_DIAMETER / PULSES_PER_REVOLUTION;
float orientation_angle, disp_body;

// Old Variables
int count_R = 0; // For Encoders
int count_L = 0;

void calculate_traveling()
{
  int count_R = cummulativePos0(); // Get encoder values
  int count_L = cummulativePos1();

  int deltaPos0 = count_R - count_R_prev;
  int deltaPos1 = count_L - count_L_prev;

  count_L_prev = count_L;
  count_R_prev = count_R;

  float disp_l_wheel = deltaPos1 * meter_per_ticks;
  float disp_r_wheel = deltaPos0 * meter_per_ticks;
  Serial.print(" disp_l_wheel : ");
  Serial.print(disp_l_wheel);
  Serial.print(" | disp_r_wheel : ");
  Serial.print(disp_r_wheel);
  if (deltaPos0 == deltaPos1)
  { // The Straight line condition -> book reference Where am i ?
    x += disp_l_wheel * cos(theta);
    y += disp_l_wheel * sin(theta);
  }
  else // for circular arc equations change
  {
    orientation_angle = (disp_r_wheel - disp_l_wheel) / AXLE_LENGTH;
    disp_body = (disp_r_wheel + disp_l_wheel) / 2.0;
    x += (disp_body / orientation_angle) * (sin(orientation_angle + theta) - sin(theta));
    y -= (disp_body / orientation_angle) * (cos(orientation_angle + theta) - cos(theta));
    theta += orientation_angle;
    Serial.print(" OR : ");
    Serial.print(orientation_angle);
    Serial.print(" | theta : ");
    Serial.print(theta);
    while (theta > PI)
      theta -= (2.0 * PI);
    while (theta < -PI)
      theta += (2.0 * PI);
  }
  Serial.print(" count_L : ");
  Serial.print(count_L_prev);
  Serial.print(" | count_R : ");
  Serial.println(count_R_prev);
}
