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
        return bnw;
    }
    int getStep()
    {
	return step;
    }
    void setStep(int s)
    {
	step = s;
    }
    void handle_pic(cv::VideoCapture cap);
    picResult find_direction();

private:
    cv::Mat bnw;
    int middle;
    int middle2;
    int step;
};
