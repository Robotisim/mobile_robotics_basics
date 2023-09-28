cmake_minimum_required(VERSION 3.10)
project(MotorControlProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include/crow)

add_executable(motor_control_app src/main.cpp src/motor_control.cpp src/robot_motion.cpp src/camera_controller.cpp)
target_include_directories(motor_control_app PRIVATE include )
target_link_libraries(motor_control_app Threads::Threads rt pigpiod_if2 ${OpenCV_LIBS})
