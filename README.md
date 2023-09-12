# ESP32 ArduinoOTA

ESP32 ArduinoOTA is a project that enables Over-The-Air (OTA) firmware updates for ESP32 devices using PlatformIO in Visual Studio Code. This allows you to update your ESP32 firmware wirelessly without the need for physical connections.

## Table of Contents

- [Prerequisites](#prerequisites)
- [Getting Started](#getting-started)
  - [1. Wi-Fi Configuration](#1-wi-fi-configuration)
  - [2. OTA Update Settings](#2-ota-update-settings)
  - [3. Uploading the Code](#3-uploading-the-code)
- [Performing OTA Updates](#performing-ota-updates)
  - [1. Connecting to Wi-Fi](#1-connecting-to-wi-fi)
  - [2. Initiating OTA Updates](#2-initiating-ota-updates)
  - [3. Automatic Reboot](#3-automatic-reboot)
- [PlatformIO Configuration](#platformio-configuration)
- [Troubleshooting](#troubleshooting)
- [Contributors](#contributors)
- [License](#license)

## Prerequisites

Before you begin, make sure you have the following:

- An ESP32 development board.
- PlatformIO extension installed in Visual Studio Code.
- A stable Wi-Fi network with SSID and password.
- Your Wi-Fi network credentials (`SSID` and `Password`) stored in a file named `credentials.h`. Make sure to replace `SSID` and `Password` with your actual Wi-Fi credentials.

## Getting Started

### 1. Wi-Fi Configuration

To configure your Wi-Fi credentials, create a file named `credentials.h` in the same directory as your main source file and define your Wi-Fi credentials like this:

```cpp
// credentials.h
const char* SSID = "YourWiFiSSID";
const char* Password = "YourWiFiPassword";
```
Replace "YourWiFiSSID" and "YourWiFiPassword" with your actual Wi-Fi credentials.

### 2. OTA Update Settings
In your code, configure the OTA update settings in the `setup()` function:

- Set the ESP32 hostname: `ArduinoOTA.setHostname("Esp32");`
- (Optional) Set an OTA update password: `ArduinoOTA.setPassword("admin");`
### 3. Uploading the Code
Compile and upload your ESP32 code to the device as usual using PlatformIO.

Once the code is uploaded, open the Serial Monitor to view the ESP32's output.

The ESP32 will attempt to connect to the specified Wi-Fi network. If the connection fails, it will automatically reboot and retry.

When the ESP32 is successfully connected to Wi-Fi, it will enter OTA update mode. You will see a message in the Serial Monitor indicating it's ready for updates.

## Performing OTA Updates

### 1. Connecting to Wi-Fi
Ensure that your ESP32 is connected to the same Wi-Fi network as your development machine.

### 2. Initiating OTA Updates
Open the Arduino IDE or any other OTA update tool compatible with ESP32.

Search for available devices for OTA updates. You should see your ESP32 listed with the hostname you configured.

Initiate the OTA update. The ESP32 will receive and apply the new firmware over Wi-Fi.

**Note:** If you are running the OTA update for the first time, consider the following points:

- For the initial setup, it's recommended to run the basic OTA code from the examples of the ArduinoOTA library using a USB cable connection to ensure everything is working.
- When using PlatformIO, make necessary changes in the `platformio.ini` file for schemes and provide the ESP32's IP address.
- After successfully uploading the code over Wi-Fi for the first time, you might face difficulties running OTA updates again. To resolve this, ensure that:
  - When running the basic OTA sketch in PlatformIO, the `platformio.ini` file should be in its most basic form; excessive configuration may interfere with OTA updates. Alternatively, you can use Arduino IDE to run the basic OTA sketch with a USB cable connection.
  - To enable repeated OTA updates, make sure to include the OTA code in the new sketches you upload. For example, if you want to update a blink program, copy the three sections (Global, setup, and loop) of the blink program and paste them into the corresponding sections of the OTA program, leaving the OTA-related code untouched. This way, you can download and change your blink program as many times as you want using OTA.

### 3. Automatic Reboot
The ESP32 will automatically reboot after a successful OTA update.

Monitor the Serial Monitor for status updates during the OTA update process.

## PlatformIO Configuration
To configure PlatformIO for your ESP32 device, add the following information to your `platformio.ini` file:
```ini
[env:esp32doit-devkit-v1]
platform = espressif32
board = esp32doit-devkit-v1
framework = arduino
upload_port = 192.168.100.15
upload_protocol = espota
monitor_speed = 115200
monitor_rts = 0
monitor_dtr = 0
monitor_port = /dev/ttyUSB0
board_build.partitions = min_spiffs.csv
lib_deps = moononournation/GFX Library for Arduino@^1.3.5
```
## Troubleshooting
If you encounter any issues during the OTA update process, check the Serial Monitor for error messages. Common issues include authentication failures, connection problems, and update errors.

Refer to the error messages in the code for more information on specific OTA update errors.

## Contributors

- [Ibrahim Bin Mansur](https://github.com/ibrahimmansur4)

If you would like to contribute to this project, please fork the repository and open a pull request with your changes.

## License
This project is open-source and available under the [MIT License](LICENSE).