#include "motor_control.h"

// Define channels for LEDC functions
#define channel_l1 0
#define channel_l2 1
#define channel_r1 2
#define channel_r2 3

// Frequency for LEDC function
#define freq 5000

// Resolution for LEDC function
#define resolution 8

// Define a variable to hold the current speed
int currentSpeed = 0; // Initial speed (adjust as needed)

void moveForward(int speed)
{
  ledcWrite(channel_l1, 0);
  ledcWrite(channel_r1, 0);
  ledcWrite(channel_l2, speed);
  ledcWrite(channel_r2, speed);
  delay(20);
}

void moveBackward(int speed)
{
  ledcWrite(channel_l1, speed);
  ledcWrite(channel_r1, speed);
  ledcWrite(channel_l2, 0);
  ledcWrite(channel_r2, 0);
  delay(20);
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

void speedUp()
{
  currentSpeed += 30;
  if (currentSpeed > 255)
  {
    currentSpeed = 255; // Limit the speed to the maximum value (255)
    if (data == "forward")
    {
      moveForward(currentSpeed); // Set the speed as needed (0 to 255)
    }
    else if (data == "backward")
    {
      moveBackward(currentSpeed); // Set the speed as needed (0 to 255)
    }
  }
}

void speedDown()
{
  currentSpeed -= 30;
  if (currentSpeed < 0)
  {
    currentSpeed = 0; // Limit the speed to the minimum value (0)
    if (data == "forward")
    {
      moveForward(currentSpeed); // Set the speed as needed (0 to 255)
    }
    else if (data == "backward")
    {
      moveBackward(currentSpeed); // Set the speed as needed (0 to 255)
    }
  }
}

void processData(String data)
{
  // Convert the received data to lowercase for case-insensitive comparison
  data.toLowerCase();

  // Process the received data and call the appropriate functions
  if (data == "forward")
  {
    moveForward(currentSpeed); // Set the speed as needed (0 to 255)
  }
  else if (data == "backward")
  {
    moveBackward(currentSpeed); // Set the speed as needed (0 to 255)
  }
  else if (data == "right")
  {
    turnRight(); // Set the speed as needed (0 to 255)
  }
  else if (data == "left")
  {
    turnLeft(); // Set the speed as needed (0 to 255)
  }
  else if (data == "stop")
  {
    stopMotors();
  }
  else if (data == "up")
  {
    speedUp();
  }
  else if (data == "down")
  {
    speedDown();
  }
}
