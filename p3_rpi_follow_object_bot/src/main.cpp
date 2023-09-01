#include "robot_motion.hpp"

int main() {
    Robot myRobot;

    myRobot.moveForward();
    time_sleep(3);
    myRobot.stop();
    time_sleep(3);
    myRobot.turnLeft();
    time_sleep(3);
    myRobot.stop();
    time_sleep(3);
    myRobot.turnRight();
    time_sleep(3);
    myRobot.stop();
    time_sleep(3);
    myRobot.moveReverse();
    time_sleep(3);
    myRobot.stop();

    return 0;
}
