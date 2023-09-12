# Dead Reckoning with AS5600 Encoders on ESP32

## Table of Contents

- [Project Overview](#project-overview)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Custom Libraries](#custom-libraries)
  - [MotorControl](#motorcontrol)
  - [EncoderControl](#encodercontrol)
  - [AS5600](#as5600)
  - [dead_Reckoning](#dead_reckoning)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Contributors](#contributors)
- [License](#license)

## Project Overview

This project demonstrates dead reckoning using AS5600 magnetic encoders with an ESP32 microcontroller. Dead reckoning is a method of estimating the current position of a mobile robot based on how far and in what direction it has traveled since a known starting point.

## Hardware Requirements

- ESP32 Microcontroller
- AS5600 Magnetic Encoders (2x)
- Motor Drivers (compatible with ESP32)
- Wheels and Motors for the Robot
- Power Supply
- Serial Monitor (for debugging)

## Software Requirements

- PlatformIO (IDE)
- Arduino Framework for ESP32
- Custom Libraries (included in the project)

## Custom Libraries

### MotorControl

The `MotorControl` library provides functions and configurations for controlling motors connected to the ESP32. It abstracts the low-level motor control operations, making it easier to drive the robot.

```cpp
void setupMotors() {
  // Set the motor control pins to outputs
  pinMode(ml_1, OUTPUT);
  pinMode(ml_2, OUTPUT);
  pinMode(mr_1, OUTPUT);
  pinMode(mr_2, OUTPUT);

  // Setup LEDC
  ledcSetup(channel_l1, PWM_FREQ, resolution);
  ledcSetup(channel_l2, PWM_FREQ, resolution);
  ledcSetup(channel_r1, PWM_FREQ, resolution);
  ledcSetup(channel_r2, PWM_FREQ, resolution);

  // Attach the channels to the GPIOs
  ledcAttachPin(ml_1, channel_l1);
  ledcAttachPin(ml_2, channel_l2);
  ledcAttachPin(mr_1, channel_r1);
  ledcAttachPin(mr_2, channel_r2);

  Serial.begin(115200);
  Serial.println("Motors Starting");
}
```

### EncoderControl

The `EncoderControl` library facilitates the setup and control of encoders like AS5600. It includes functions for initializing encoders and reading encoder values. This library enables precise tracking of wheel movement.

```cpp
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
    // Serial.println(cummulative0);
    return cummulative0;
  }
}
```
### AS5600

The `AS5600` library is designed for interfacing with AS5600 magnetic encoders. It provides functions to interact with AS5600, read the encoder's position, and set the initial position. This library is essential for accurate dead reckoning.

### Dead_Reckoning

The `dead_Reckoning` library combines motor control, encoder handling, and dead reckoning calculations. It calculates the robot's position (X and Y coordinates) based on the encoder data, allowing for real-time position estimation.

```cpp
// Fixed values
#define WHEEL_DIAMETER 0.0335
#define PULSES_PER_REVOLUTION 4096.0
#define AXLE_LENGTH 0.067
#define PI 3.1415926535897932384626433832795

// New Variables
float disp_r_wheel = 0;
float disp_l_wheel = 0;
...

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

    while (theta > PI)
      theta -= (2.0 * PI);
    while (theta < -PI)
      theta += (2.0 * PI);
  }
}
```
This code calculates the position (X and Y coordinates) of a mobile robot using dead reckoning based on AS5600 encoders' data. It accounts for both straight-line and circular motion and provides real-time position estimation. 

## Getting Started

1. Ensure you have the ESP32 hardware set up with AS5600 encoders, motors, and other necessary components.

2. Install PlatformIO for VSCode if you haven't already.

3. Open the project in VSCode using PlatformIO.

4. Upload the code to your ESP32 microcontroller.

5. Open the Serial Monitor to view the X and Y coordinates of your robot's estimated position. Adjust the delay time in the `loop` function for your desired update rate.

## Usage

The code provided serves as a basic example of dead reckoning with AS5600 encoders. You can extend and modify it to suit your robot's specific requirements and integrate additional sensors for improved accuracy.

## Contributors

- [Ibrahim Bin Mansur](https://github.com/ibrahimmansur4)
- [Muhamamd Luqman](https://github.com/noshluk2)

## License

This project is open-source and available under the [MIT License](LICENSE).
