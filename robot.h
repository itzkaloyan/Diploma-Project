#pragma once
#include "opencv2/opencv.hpp"
#include <string>

struct Result
{
    int angle = -1;
    int direction = -1;
};

class Robot
{
public:
    Robot() = default;
    cv::Mat getBnw()
    {
        return bnw;
    }
    cv::Mat handle_pic(std::string fileName);
    Result find_direction();

private:
    cv::Mat bnw;
};