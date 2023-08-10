#include "EncoderControl.h"
#include "AS5600.h"
#include <Wire.h>
#include <SPI.h>
#include "MotorControl.h"

AS5600 as5600_0(&Wire); // use default Wire
AS5600 as5600_1(&Wire1);

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
  }
}

void readEncoderAngle0()
{
  if (!as5600_0.begin())
  {
  }
  else
  {
    int angle1 = as5600_0.rawAngle() * AS5600_RAW_TO_DEGREES;
    Serial.print("Encoder 0 Angle: ");
    Serial.print(angle1);
    // if (as5600_0.getRevolutions() > 1){
    //   // motorRightStop();
    //   stopMotors();
    // }
  }
}

void readEncoderAngle1()
{
  if (!as5600_1.begin())
  {
  }
  else
  {
    int angle2 = as5600_1.rawAngle() * AS5600_RAW_TO_DEGREES;
    Serial.print("Encoder 1 Angle: ");
    Serial.print(angle2);
  }
}

void getEncoderSpeed0()
{
  if (!as5600_0.begin())
  {
  }
  else
  {
    float speed1 = (PI * WHEEL_DIAMETER * as5600_0.getAngularSpeed(AS5600_MODE_RPM)) / 60.0;
    Serial.print(" degrees | Speed 0 (cm/s): ");
    Serial.println(speed1, 2);
    Serial.print("Encoder 0 Speed (RPM): ");
    Serial.println(as5600_0.getAngularSpeed(AS5600_MODE_RPM));
  }
}
void getEncoderSpeed1()
{
  if (!as5600_1.begin())
  {
  }
  else
  {
    float speed2 = (PI * WHEEL_DIAMETER * as5600_1.getAngularSpeed(AS5600_MODE_RPM)) / 60.0;
    Serial.print(" degrees | Speed 1 (cm/s): ");
    Serial.println(speed2, 2);
    Serial.print("Encoder 1 Speed (RPM): ");
    Serial.println(as5600_1.getAngularSpeed(AS5600_MODE_RPM));
  }
}

int getEncoderRevolutions0()
{
  if (!as5600_0.begin())
  {
  }
  else
  {
    static uint32_t lastTime = 0;

    //  set initial position
    as5600_0.getCumulativePosition();

    //  update every 100 ms
    //  should be enough up to ~200 RPM
    if (millis() - lastTime >= 100)
    {
      lastTime = millis();
      Serial.print(as5600_0.getCumulativePosition());
      Serial.print("Revolution 0: ");
      Serial.println(as5600_0.getRevolutions());
    }
    int revolution0 = as5600_0.getRevolutions();
    return revolution0;
  }
}

int getEncoderRevolutions1()
{
  if (!as5600_1.begin())
  {
  }
  else
  {
    static uint32_t lastTime = 0;

    //  set initial position
    as5600_1.getCumulativePosition();

    //  update every 100 ms
    //  should be enough up to ~200 RPM
    if (millis() - lastTime >= 100)
    {
      lastTime = millis();
      Serial.print(as5600_1.getCumulativePosition());
      Serial.print("Revolution 1: ");
      Serial.println(as5600_1.getRevolutions());
    }
    int revolution1 = as5600_1.getRevolutions();
    return revolution1;
  }
}

int resolution_0()
{
  if (!as5600_0.begin())
  {
  }
  else
  {
    Serial.print("Resolution 1: ");
    Serial.println(as5600_0.readAngle());
    int resolution0 = as5600_0.readAngle();
    return resolution0;
  }
}
int resolution_1()
{
  if (!as5600_1.begin())
  {
  }
  else
  {
    Serial.print("Resolution 2: ");
    Serial.println(as5600_1.readAngle());
    int resolution1 = as5600_1.readAngle();
    return resolution1;
  }
}