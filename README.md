# WiFi Controlled Robot with Video Streaming

This project enables you to control a robot remotely using a mobile app and stream video from an ESP32-CAM. The robot's movements can be controlled through a mobile app, and you can view live video streaming from the robot's camera.

## Table of Contents
- [Project Overview](#project-overview)
- [Hardware Components](#hardware-components)
- [Software Components](#software-components)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Custom Libraries](#custom-libraries)
- [Contributors](#contributors)
- [License](#license)

## Project Overview

This project integrates a mobile app, ESP32-CAM, and custom software to create a WiFi-controlled robot with live video streaming capabilities. It allows you to control the robot's movements and view its surroundings in real-time using a simple mobile app interface.

## Hardware Components

To build this project, you will need the following hardware components:

- ESP32-CAM
- Robot chassis with motors and wheels
- Motor driver board
- Power supply for the robot
- Mobile device (for running the control app)

## Software Components

The software components used in this project include:

- [PlatformIO](https://platformio.org/) for ESP32-CAM programming in VSCode.
- Custom Arduino libraries for motor control, WiFi communication, and camera configuration.
- Android app (APK) for controlling the robot and viewing the video stream.

## Getting Started

Follow these steps to get started with the project:

1. **Setup Hardware:**
   - Assemble the robot chassis, motors, wheels, and motor driver board according to your design.
   - Connect the ESP32-CAM to the robot's chassis and ensure it's securely mounted.
   - Connect all necessary wires and power sources.

2. **Flash the ESP32-CAM:**
   - Use PlatformIO in VSCode to upload the code to your ESP32-CAM.
   - Make sure you have the required libraries installed.

3. **Install the Control App:**
   - Install the provided Android APK on your mobile device.

4. **Establish WiFi Connection:**
   - Power on the robot and ESP32-CAM.
   - Connect your mobile device to the robot's WiFi network using the provided credentials.

5. **Start Controlling:**
   - Open the control app on your mobile device.
   - Use the app's interface to send commands to the robot for movement.
   - Observe the robot's movements on its live video stream.

## Usage

- Connect to the robot's WiFi network using the provided credentials.
- Open the mobile app and establish a connection with the robot.
- Use the app's interface to send commands to the robot, such as moving forward, backward, or adjusting its speed.
- Observe the robot's movements on its live video stream.

## Custom Libraries

This project uses custom libraries to simplify development:

- `motor_control`: Provides functions for controlling the robot's motors.
- `wifi_communication`: Handles WiFi communication and client-server interactions.
- `camera_configuration`: Configures the ESP32-CAM camera settings for video streaming.

### Motor Control (motor_control)

```cpp
// Example motor control code snippet
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
```
### WiFi Configuretion (wifi_communication)
```cpp
// Example WiFi communication code snippet
String checkClient(void)
{
  while (!client.available())
    delay(1);

  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length() - 9, 9);

  return request;
}
```
### Camera Configuretion (camera_http)
```cpp
void startCameraServer()
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.max_uri_handlers = 17;

    // ... (HTTPD configuration code)
     httpd_uri_t back_uri = {
        .uri       = "/backward",
        .method    = HTTP_GET,
        .handler   = back_handler,
        .user_ctx  = NULL
    };

    httpd_uri_t stop_uri = {
        .uri       = "/stop",
        .method    = HTTP_GET,
        .handler   = stop_handler,
        .user_ctx  = NULL
    };
    log_i("Starting web server on port: '%d'", config.server_port);
    if (httpd_start(&camera_httpd, &config) == ESP_OK)
    {
        // Register URI handlers
        httpd_register_uri_handler(camera_httpd, &index_uri);
        httpd_register_uri_handler

        // Register custom URI handlers for robot control
        httpd_register_uri_handler(camera_httpd, &go_uri); 
        httpd_register_uri_handler(camera_httpd, &back_uri); 
        httpd_register_uri_handler(camera_httpd, &stop_uri); 
        httpd_register_uri_handler(camera_httpd, &left_uri);
        httpd_register_uri_handler(camera_httpd, &right_uri);
        httpd_register_uri_handler(camera_httpd, &up_uri);
        httpd_register_uri_handler(camera_httpd, &down_uri);
    }
}
```

The `startCameraServer` function initializes the HTTP server for serving video streams and registering URI handlers for different robot control commands.

- The `config` variable stores the default HTTPD configuration with a maximum of 17 URI handlers.
- URI handlers for various commands, including index, status, capture, and more, are registered.
- Custom URI handlers for robot control commands like forward, backward, stop, left, right, up, and down are also registered.

These handlers enable the robot to receive control commands and serve live video streams.

#### Custom URI Handlers
The custom URI handlers defined in this code snippet enable the robot to respond to control commands sent via HTTP GET requests. For example, sending a request to **/forward** will trigger the `go_handler` function, instructing the robot to move forward.

This code is a critical part of the project, as it defines how the robot interprets and acts upon incoming commands from the mobile app.
## Contributors

- [Ibrahim Bin Mansur](https://www.linkedin.com/in/ibrahim-bin-mansur-4a7012157/)
- [Khubaib Iftikhar](https://www.linkedin.com/in/khubaib-iftikhar-795083272/)

## License

This project is licensed under the MIT License. See the [LICENSE.md](LICENSE.md) file for details.
