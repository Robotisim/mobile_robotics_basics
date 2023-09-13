# AS5600 Repeatability Test

## Table of Contents
- [Introduction](#introduction)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Custom Libraries](#custom-libraries)
- [Setup](#setup)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This project is designed to perform repeatability tests on AS5600 magnetic encoders using an ESP32 microcontroller and the VSCode PlatformIO IDE. The AS5600 is a magnetic position sensor that can be used in various applications where accurate angular measurements are required.

## Hardware Requirements

To replicate this project, you will need the following hardware components:
- ESP32 development board
- AS5600 magnetic encoders (2 units for this project)
- Motor control hardware (e.g., motor drivers and motors)
- Connecting wires
- Power supply for motors and ESP32
- Computer with the VSCode PlatformIO IDE installed

## Software Requirements

The software requirements for this project include:

- [VSCode](https://code.visualstudio.com/)
- [PlatformIO Extension for VSCode](https://platformio.org/install/ide?install=vscode)
- Library for AS5600.

## Custom Libraries

### MotorControl Library

The `MotorControl` library provides functions for controlling motors connected to the ESP32. It offers functions like `moveForward()`, `moveBackward()`, `motorLeftStop()`, `motorRightStop()`, and more to control the movement of your motors. Here's an example of how to use it:

```cpp
#include "MotorControl.h"

// ... (Setup and other code)

void loop() {
  // Move forward
  moveForward(150);

  // Delay or add other logic here

  // Stop the motors
  motorRightStop();
  motorLeftStop();
}

```




Certainly, you can create a "Custom Libraries" subheading in your README.md to describe your custom libraries and provide code snippets. Here's how you can structure it:

markdown
Copy code
## Custom Libraries

### MotorControl Library

The `MotorControl` library provides functions for controlling motors connected to the ESP32. It offers functions like `moveForward()`, `moveBackward()`, `motorLeftStop()`, `motorRightStop()`, and more to control the movement of your motors. Here's an example of how to use it:

```cpp
#include "MotorControl.h"

// ... (Setup and other code)

void loop() {
  // Move forward
  moveForward(150);

  // Delay or add other logic here

  // Stop the motors
  motorRightStop();
  motorLeftStop();
}

```
### Encoder Control Library
The `EncoderControl` library interfaces with the AS5600 magnetic encoders, allowing you to read encoder angles, speeds, and revolutions. It also provides functions like `setupEncoder0()` and `setupEncoder1()` to initialize encoders. Here's an example of how to use it:

```cpp
#include "EncoderControl.h"
AS5600 as5600_0(&Wire); // use default Wire

// ... (Setup and other code)
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
```
## Setup

1. **Hardware Connections**: Connect the AS5600 magnetic encoders to the ESP32 and motor control hardware following your project's circuit diagram.

2. **Install Software**:
   - Install VSCode and the PlatformIO extension.
   - Install the required libraries for AS5600 and motor control through PlatformIO.

3. **Upload Code**: Open this project in VSCode, connect your ESP32 to your computer, and upload the code to the ESP32.

4. **Power Up**: Ensure that all hardware components are powered up and ready for testing.

## Usage

The code in this project performs repeatability tests on AS5600 magnetic encoders. It rotates motors connected to the encoders and monitors the encoder revolutions. When the specified conditions are met (e.g., encoder revolutions exceeding a threshold), the motors stop. 

To use this project, follow these steps:
1. Upload the code to your ESP32 as explained in the setup section.

2. Power up your hardware setup, ensuring that the motors and encoders are correctly connected.

3. Open the Serial Monitor in VSCode to monitor the progress and results of the repeatability tests.

4. Observe the behavior of the motors and the encoder readings as the tests run.

5. The code is currently set to stop the motors when specific encoder revolution conditions are met. You can modify these conditions to suit your specific testing requirements.

## Contributors

- [Ibrahim Bin Mansur](https://github.com/ibrahimmansur4)

Contributions to this project are welcome. If you have ideas for improvements or encounter issues, please open an issue or submit a pull request. We appreciate your input.

## License

This project is open-source and available under the [MIT License](LICENSE). You are free to use, modify, and distribute this code for your projects.
