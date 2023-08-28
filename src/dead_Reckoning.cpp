//  http://www-personal.umich.edu/~johannb/position.htm book link

#include <Arduino.h>
#include "dead_Reckoning.h"
#include "EncoderControl.h"
//Fixed values
#define WHEEL_DIAMETER 0.0335
#define PULSES_PER_REVOLUTION 4096.0
#define AXLE_LENGTH  0.067
#define PI 3.1416

// New Variables
float disp_r_wheel       = 0;
float disp_l_wheel       = 0;
int count_R_prev         = 0;
int count_L_prev         = 0;             
float x                  = 0;
float y                  = 0;
float theta              = 0;
float meter_per_ticks    = PI * WHEEL_DIAMETER / PULSES_PER_REVOLUTION;
float orientation_angle , disp_body;

// Old Variables
int count_R              = 0;                          //For Encoders
int count_L              = 0;  
          
void calculate_traveling(){
      
    count_L_prev = count_L;
    count_R_prev = count_R;
    count_L      = cummulativePos0();
    count_R      = cummulativePos1();
    disp_l_wheel = (float)count_L_prev * meter_per_ticks;              // geting distance in meters each wheel has traveled
    disp_r_wheel = (float)count_R_prev * meter_per_ticks;
    
    if (count_L_prev == count_R_prev)
    {                                                                  // The Straight line condition -> book reference Where am i ?
      x += disp_l_wheel * cos(theta);
      y += disp_l_wheel * sin(theta);
    }
    else                                                               // for circular arc equations change
    { orientation_angle = (disp_r_wheel - disp_l_wheel)/AXLE_LENGTH;
      disp_body   = (disp_r_wheel + disp_l_wheel) / 2.0;
      x += (disp_body/orientation_angle) * (sin(orientation_angle + theta) - sin(theta));
      y -= (disp_body/orientation_angle) * (cos(orientation_angle + theta) - cos(theta));
      theta += orientation_angle;

     
       while(theta > PI)
         theta -= (2.0*PI);
       while(theta < -PI) 
         theta += (2.0*PI); 
    }
} 
  

