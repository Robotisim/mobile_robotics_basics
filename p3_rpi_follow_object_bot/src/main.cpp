#include "robot_motion.hpp"
#include "camera_controller.hpp"

int main(){
    // Robot_motion follow_object_bot;
    // follow_object_bot.moveForward();
    // time_sleep(3);
    // follow_object_bot.stop();
    // time_sleep(1);

    // follow_object_bot.moveReverse();
    // time_sleep(3);
    // follow_object_bot.stop();
    // time_sleep(1);

    // follow_object_bot.turnRight();
    // time_sleep(3);
    // follow_object_bot.stop();
    // time_sleep(1);

    // follow_object_bot.turnLeft();
    // time_sleep(3);
    // follow_object_bot.stop();
    // time_sleep(1);


    CameraController camera;
    camera.recordVideo(10,"lquman"); // Record 10 seconds of video
// camera.captureImage("my_image");
    // camera.startStreaming();  // This will start the HTTP server on port 4000



    return 0;
}