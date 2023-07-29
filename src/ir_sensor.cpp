#include "ir_sensor.h"
#include "motor_control.h"
#include "pi_controller.h"

// Create an instance of the PI controller
PIController piController(1.5, 0.1); // Initial gains

// Define the states for the state machine
enum State
{
    STATE_FORWARD,
    STATE_SLIGHT_LEFT,
    STATE_SLIGHT_RIGHT,
    STATE_HARD_LEFT,
    STATE_HARD_RIGHT,
    STATE_U_TURN,
    STATE_STOP
};

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

    // Calculate error based on sensor readings
    float error = s1 * 4 + s2 * 3 + s3 * 2 + s4 * (-3) + s5 * (-4);
    // Calculate the control signal (direction adjustment) using the PI controller
    float controlSignal = piController.calculateControlSignal(error);

    State currentState;

    if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 1 && s5 == 1)
    {
        currentState = STATE_FORWARD;
    }
    else if (s1 == 1 && s2 == 0 && s3 == 0 && s4 == 1 && s5 == 1)
    {
        currentState = STATE_SLIGHT_LEFT;
    }
    else if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 0 && s5 == 1)
    {
        currentState = STATE_SLIGHT_RIGHT;
    }
    else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 1 && s5 == 1)
    {
        currentState = STATE_HARD_LEFT;
    }
    else if (s1 == 1 && s2 == 1 && s3 == 0 && s4 == 0 && s5 == 0)
    {
        currentState = STATE_HARD_RIGHT;
    }
    else if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0 && s5 == 0)
    {
        currentState = STATE_FORWARD;
    }
    else if (s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1 && s5 == 1)
    {
        currentState = STATE_U_TURN;
    }
    else
    {
        currentState = STATE_STOP;
    }

    // Implement the state machine behavior
    switch (currentState)
    {
    case STATE_FORWARD:
        moveForward(255);
        break;
    case STATE_SLIGHT_LEFT:
        // Make a slight left adjustment
        turnLeft(180 - controlSignal);
        break;
    case STATE_SLIGHT_RIGHT:
        // Make a slight right adjustment
        turnRight(180 + controlSignal);
        break;
    case STATE_HARD_LEFT:
        // Make a hard left turn
        turnLeft(255);
        break;
    case STATE_HARD_RIGHT:
        // Make a hard right turn
        turnRight(255);
        break;
    case STATE_U_TURN:
        // Perform a U-turn
        moveBackward(200);
        delay(500);
        if (random(0, 2) == 0)
        {
            turnLeft(180);
        }
        else
        {
            turnRight(180);
        }
        delay(500);
        break;
    case STATE_STOP:
        // Stop
        stopMotors();
        break;
    default:
        // Handle unexpected state (optional)
        break;
    }
    delay(10);
}
