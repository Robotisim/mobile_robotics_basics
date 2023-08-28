# ESP32 Robot Control System

This project implements a robot control system using ESP32. The system includes motor control, position calculation, and communication over Wi-Fi. The robot's position is calculated based on encoder readings and can be controlled remotely.

## Hardware Requirements

- ESP32 board
- AS5600 magnetic encoder
- Motor drivers (for example, L298N)
- Wi-Fi module (e.g., ESP32)
- Wheels with encoders
- Power supply

## Libraries Used

- WiFi
- WiFiUdp
- Wire
- AS5600 (for encoder communication)

## Code Explanation

- The code calculates the robot's position based on encoder readings and motion equations.
- Wifi control is provided to drive the robot using predefined commands (`'f'` for forward, `'b'` for reverse, etc.).
- Wi-Fi communication is used to send the robot's position to a server.
- AS5600 encoder library is used to integrate the AS5600 encoder's built-in functions.

## File Structure

- `main.cpp`: Main Arduino code file.
- `MotorControl.h` , `EncoderControl.h`, `dead_Reckoning.h`: Header file containing variable and function declarations.
- `AS5600.h`, `AS5600.cpp`: AS5600 encoder library files (if required).

## How to Use

1. Connect the hardware components as per the wiring diagram.
2. Upload the `main.cpp` code to your ESP32 board.
3. Install the required libraries.
4. Power on the robot and establish Wi-Fi connections.
5. Use a Bluetooth terminal app to send commands to control the robot.
6. The robot's position will be calculated and sent over Wi-Fi to the specified server.

## Wiring Diagram

Insert your wiring diagram here if you have one.

## Acknowledgments

This project is inspired by [source link](http://www-personal.umich.edu/~johannb/position.htm).

## License

This project is licensed under the [MIT License](LICENSE).

