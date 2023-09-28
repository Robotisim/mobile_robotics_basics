#ifndef CAMERA_CONTROLLER_HPP
#define CAMERA_CONTROLLER_HPP

#include <opencv2/opencv.hpp>
#include <string>

class CameraController {
public:
    CameraController();
    ~CameraController();
    void recordVideo(int timeSecs, const std::string& name);
    void captureImage(const std::string& name);
    void startStreaming();
private:
    cv::VideoCapture cap;
};

#endif // CAMERA_CONTROLLER_HPP
