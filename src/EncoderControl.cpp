#include "EncoderControl.h"
#include "AS5600.h"
#include <Wire.h>
#include <SPI.h>
#include "MotorControl.h"

AS5600 as5600_0(&Wire); // use default Wire
AS5600 as5600_1(&Wire1);


/*
The AS5600 allows controlling the direction of the magnet rotation with the DIR pin. 
If DIR is connected to GND (DIR = 0) a clockwise rotation viewed from the top will 
generate an increment of the calculated angle. If the DIR pin is connected 
to VDD (DIR = 1) an increment of the calculated angle will happen with 
counter-clockwise rotation.
*/
void setupEncoder0()
{
  Wire.begin();
  if (!as5600_0.begin())
  {
    Serial.println("Encoder 0 not connected!");
    Wire.end();
  }
  else
  {
    as5600_0.setDirection(AS5600_CLOCK_WISE); 
    Serial.println("Connect device 0: true");
    as5600_0.resetCumulativePosition(0);
  }
}

void setupEncoder1()
{
  Wire1.begin(4, 5);
  if (!as5600_1.begin())
  {
    Serial.println("Encoder 1 not connected!");
    Wire1.end();
  }
  else
  {
    as5600_1.setDirection(AS5600_CLOCK_WISE);
    Serial.println("Connect device 1: true");
    as5600_1.resetCumulativePosition(0);
  }
}

int cummulativePos0()
{
  if (!as5600_0.begin())
  {
  }
  else
  {
    //  set initial position

    int cummulative0 = as5600_0.getCumulativePosition();
    //  should be enough up to ~200 RPM
    // int cummulative0 = as5600_0.readAngle();  //right
    Serial.println(cummulative0);
    return cummulative0;
  }
}

int cummulativePos1()
{
  if (!as5600_1.begin())
  {
  }
  else
  {
    //  set initial position
    
    int cummulative1 = as5600_1.getCumulativePosition();
    //  should be enough up to ~200 RPM
    // int cummulative1 = as5600_1.readAngle();
    Serial.println(cummulative1);
    return cummulative1;
  }
}