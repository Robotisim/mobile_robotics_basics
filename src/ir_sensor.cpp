#include "ir_sensor.h"
#include "motor_control.h"

void setupSensor()
{
    pinMode(ir1, INPUT);
    pinMode(ir2, INPUT);
    pinMode(ir3, INPUT);
    pinMode(ir4, INPUT);
    pinMode(ir5, INPUT);
}

void getData()
{
    int s1 = digitalRead(ir1); // Left Most Sensor
    int s2 = digitalRead(ir2); // Left Sensor
    int s3 = digitalRead(ir3); // Middle Sensor
    int s4 = digitalRead(ir4); // Right Sensor
    int s5 = digitalRead(ir5); // Right Most Sensor

        // if only middle sensor detects black line
    if ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1))
    {
        // going forward with full speed
        moveForward(255);
    }
    // if only left sensor detects black line
    if ((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
    {

        turnLeft();
    }
    if ((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1))
    {

        turnLeft();
    }
    // if only right sensor detects black line
    if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1))
    {
        turnRight();
    }

    // if only right most sensor detects black line
    if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0))
    {
        turnRight();
    }

    // if middle and right sensor detects black line
    if ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1))
    {
        turnRight();
    }

    // if middle and left sensor detects black line
    if ((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
    {
        turnLeft();
    }

    // if middle, left and left most sensor detects black line
    if ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
    {
        turnLeft();
    }

    // if middle, right and right most sensor detects black line
    if ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))
    {
        turnRight();
    }

    // if all sensors are on a black line
    if ((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
    {
        // stop
        stopMotors();
    }
}
