#pragma once
#include "opencv2/opencv.hpp"
#include <string>

struct picResult
{
    picResult() = default;
    int angle = -1;
    int direction = -1;

private:
};

class Robot
{
public:
    Robot() = default;
    cv::Mat getBnw()
    {
        return bnw;
    }
    void handle_pic(cv::VideoCapture cap);
    picResult find_direction();

private:
    cv::Mat bnw;
};
