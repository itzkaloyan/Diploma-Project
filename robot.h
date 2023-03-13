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
    Robot()
    {
        step = 0;
    }
    cv::Mat getBnw()
    {
        return result;
    }
    int getStep()
    {
        return step;
    }
    void setStep(int s)
    {
        step = s;
    }
    void handle_pic(const cv::Mat &inframe);
    picResult find_direction();

private:
    cv::Mat result;
    cv::Mat frame;
    long lowerMid;
    long upperMid;
    long rightMid;
    long leftMid;
    int step;
};
