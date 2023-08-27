# Line-Following Robot Project

Welcome to the Line-Following Robot project repository! This project involves building an intelligent robot capable of autonomously following lines on the ground using infrared sensors and a PI controller. The robot is powered by an ESP32 microcontroller, and features a custom OLED display for real-time monitoring of key control parameters. This README provides an overview of the project components, setup instructions, and usage guidelines.

## Project Overview

The Line-Following Robot project consists of several components:

- **ESP32 Microcontroller:** The brains of the robot, responsible for processing sensor data, controlling motors, and communicating with external devices over WiFi and UDP.

- **Infrared Sensors:** A set of infrared sensors are used to detect the line on the ground. These sensors provide input to the control algorithm for line following.

- **PI Controller:** A Proportional-Integral (PI) controller is implemented to maintain the robot's position on the line. This controller adjusts motor speeds based on sensor readings to keep the robot centered on the line.

- **Custom OLED Display:** The robot is equipped with an OLED display that provides real-time monitoring of control parameters, such as error values, PI values, and sensor readings.

- **WiFi and UDP Communication:** The robot communicates with an external device (e.g., a computer or another microcontroller) over WiFi using the User Datagram Protocol (UDP). This communication allows for remote monitoring and control of the robot.

## Getting Started

To set up the Line-Following Robot project, follow these steps:

1. **Hardware Setup:** Assemble the robot according to the provided schematics. This includes connecting the motors, infrared sensors, and the custom OLED display.

2. **Arduino IDE Setup:** Install the Arduino IDE if you haven't already, and make sure you have the necessary ESP32 board libraries installed.

3. **Library Installation:** The project uses several libraries for OLED display, WiFi communication, and motor control. Install these libraries through the Arduino Library Manager.

4. **Upload Code:** Use the Arduino IDE to upload the provided code to the ESP32 microcontroller. The code is divided into modules, such as motor control, PI controller, WiFi communication, and OLED display.

5. **WiFi Configuration:** Modify the WiFi credentials in the code to match your WiFi network's SSID and password. Also, update the server address and port for UDP communication as needed.

6. **Remote Monitoring:** Prepare the receiving device (computer or another microcontroller) to listen for UDP messages from the robot. The robot will send sensor data and control parameters to this device for monitoring.

7. **Power Up:** Power up the robot and observe its behavior. The robot should follow lines on the ground while continuously adjusting motor speeds to stay centered.

## Contents

The repository is organized as follows:

- `arduino_sketch/`: Contains the main Arduino sketch for the robot's ESP32 microcontroller.

- `motor_control/`: Includes code for controlling the robot's motors based on PI controller calculations.

- `pi_controller/`: Contains code related to the implementation of the PI controller for line following.

- `wifi_udp/`: Includes code for setting up WiFi communication and sending sensor data using the UDP protocol.

- `oled_display/`: Contains code for initializing and updating the custom OLED display with control parameters.

## Usage

1. Upload the code to the ESP32 microcontroller using the Arduino IDE.

2. Power up the robot and place it on a line. Observe its behavior as it autonomously follows the line using the PI controller.

3. Monitor real-time control parameters on the custom OLED display. This includes error values, PI values, and sensor readings.

4. Set up a receiving device to capture UDP messages sent by the robot. This allows remote monitoring and control of the robot's behavior.



## Hardware Used

- **ESP32 Microcontroller:** The main brain of the robot.
- **Infrared Sensors:** Detects the presence of the line on the ground.
- **Motors:** Controls the robot's movement.
- **Custom OLED Display:** Provides real-time feedback.
- **WiFi Module:** Enables communication with external devices.

## Software Used

- **Arduino IDE:** For writing, compiling, and uploading code.
- **LEDC Library:** Controls motor speed using PWM.
- **WiFi and WiFiUDP Libraries:** Establishes WiFi connections and sends/receives UDP packets.
- **U8g2 Library:** Interfaces with the OLED display.

## Logic and Key Code Snippets

### Sensor Reading and Error Calculation

```cpp
void read_sensor_values() {
  // Read sensor values and store in the 'sensor' array

  // Calculate error based on sensor readings
  if ((sensor[0] == 1) && (sensor[1] == 0) && ... && (sensor[4] == 0))
    error = -2;
  else if ((sensor[0] == 0) && (sensor[1] == 1) && ... && (sensor[4] == 0))
    error = 2;
  // ... more cases for different sensor combinations
  else
    error = 0; // Centered on the line.
}
```
### PI Controller Calculation
```cpp
void calculate_pid() {
  P = error;
  I = I + error;
  I = constrain(I, -I_limit, I_limit);
  PI_value = (Kp * P) + (Ki * I);
}


```
### Motor Control
```cpp
void motor_control() {
  // Calculate motor speeds based on PI controller output
  int left_motor_speed = Left_motor_speed - PI_value;
  int right_motor_speed = Right_motor_speed + PI_value;

  // Constrain motor speeds within limits
  left_motor_speed = constrain(left_motor_speed, 90, 200);
  right_motor_speed = constrain(right_motor_speed, 90, 200);

  // Set motor speeds using PWM
  ledcWrite(channel_l2, left_motor_speed);
  ledcWrite(channel_r2, right_motor_speed);
}


```
### Sending Sensor Data over WiFi using UDP
```cpp
void send_sensor_values_over_wifi() {
  // Convert sensor values to a string and send them over WiFi using UDP
  udp.beginPacket(serverAddress, serverPort);
  // ... convert and send sensor values
  udp.endPacket();
}


```
### Custom OLED Display
```cpp
void displayMultipleFloats(const char *label1, float value1, const char *label2, float value2) {
  // Display two float values on the OLED display with labels
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  // ... set cursor position and print labels and values
  u8g2.sendBuffer();
}

```

# Mathematics Behind the PI Controller
The PI controller is a control algorithm that uses two components: proportional (P) and integral (I). The proportional term responds to the current error value and adjusts the control output. The integral term accumulates past error values and addresses any steady-state error.

- The P component provides a control output proportional to the current error: P = Kp * error.

- The I component integrates past errors and corrects any accumulated error: I = I + Ki * error.

- The final control output is a combination of these components: PI_value = P + I.

## Conclusion
The Line-Following Robot project combines hardware components with software algorithms to create an autonomous robot capable of following lines on the ground. By using infrared sensors, a PI controller, and precise motor control, the robot can navigate its environment while making real-time adjustments to stay on the desired path. The integration of WiFi communication and the custom OLED display adds an extra layer of functionality and interactivity to the project.


## Contributing

Contributions to this project are welcome! If you encounter any bugs, have ideas for improvements, or want to extend the functionality, feel free to open issues and submit pull requests.

## Contact

Connect with me on LinkedIn: [Your LinkedIn Profile](#)

Let's discuss robotics, automation, and IoT!

## License

This project is licensed under the [MIT License](LICENSE).