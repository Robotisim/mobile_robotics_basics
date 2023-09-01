cmake_minimum_required(VERSION 3.10)
project(MotorControlProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)


add_executable(motor_control_app src/main.cpp src/motor_control.cpp src/robot_motion.cpp)
target_include_directories(motor_control_app PRIVATE include)
target_link_libraries(motor_control_app Threads::Threads rt pigpiod_if2)
