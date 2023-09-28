#include "camera_controller.hpp"
#include <iostream>
#include "crow_all.h"

CameraController::CameraController() {
    cap.open(0); // Open the default camera
    if (!cap.isOpened()) {
        std::cerr << "Error: Couldn't open the camera." << std::endl;
        exit(EXIT_FAILURE);
    }
    else {std::cerr << "Camera Started" << std::endl;}

}

CameraController::~CameraController() {
    cap.release();
}

void CameraController::recordVideo(int timeSecs, const std::string& name) {
    cv::VideoWriter video("data/" + name + ".avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(640, 480));
    cv::Mat frame;
    for (int i = 0; i < timeSecs * 30; ++i) {
        cap >> frame;
        video.write(frame);
        cv::waitKey(33);
    }
    video.release();
}

void CameraController::captureImage(const std::string& name) {
    cv::Mat frame;
    cap >> frame;
    if (!cv::imwrite("data/" + name + ".jpg", frame)) {
        std::cerr << "Error: Couldn't save the image." << std::endl;
    }
}


void CameraController::startStreaming() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/video")([this](crow::request& req, crow::response& res) {
        cv::Mat frame;
        this->cap >> frame; // Use this-> to access the member variable

        std::vector<uchar> buffer;
        cv::imencode(".jpg", frame, buffer);

        // Convert buffer to string
        std::string buffer_str(buffer.begin(), buffer.end());

        res.write(buffer_str);
        res.add_header("Content-Type", "image/jpeg");
        res.end();
    });

    app.port(4000).multithreaded().run();
}
