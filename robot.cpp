#include <iostream>
#include "robot.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <memory>
using json = nlohmann::json;

void Robot::handle_pic(const cv::Mat &inframe)
{
    flip(inframe, frame, -1);
    frame = frame(cv::Range(320, 480), cv::Range(0, 640));
    cvtColor(frame, result, cv::COLOR_BGR2HSV);
    const cv::Scalar lower_bound = cv::Scalar(80, 80, 80);
    const cv::Scalar higher_bound = cv::Scalar(195, 255, 255);
    cv::inRange(result, lower_bound, higher_bound, result);
    cv::bitwise_not(result, result);
    if (frame.empty())
    {
        std::cout << "Could not open or find the image!\n";
    }
}

enum direction
{
    err,
    left,
    right,
    forward
};

picResult Robot::find_direction()
{

    int rows = result.rows;
    int cols = result.cols;
    // lower
    long sumOfBottom = 0;
    long lengthOfBottom = 0;
    lowerMid = -1;
    for (int i = 0; i < cols; i++)
    {
        if (result.at<uint8_t>(rows - 1, i) < 255)
        {
            sumOfBottom = sumOfBottom + i;
            lengthOfBottom++;
        }
    }
    if (lengthOfBottom != 0)
    {
        lowerMid = sumOfBottom / lengthOfBottom;
    }
    else
    {
        std::cout << "no line detected!!!" << std::endl;
    }
    printf("%ld\n", lowerMid);
    direction dir = err;
    char dirLetter = 's';
    std::ifstream ifs("../config.json");
    json j = json::parse(ifs);
    int left = j["left"];
    int right = j["right"];
    left = left * cols;
    right = right * cols;
    char lastStep = 's';

    if (lowerMid >= right)
    {
        // the line is on the right
        dir = direction::right;
        std::cout << std::endl
                  << "RIGHT" << std::endl;
        dirLetter = 'r';
        lastStep = 'r';
    }
    else if (lowerMid <= left)
    {
        // the line is on the left
        dir = direction::left;
        std::cout << std::endl
                  << "LEFT" << std::endl;
        dirLetter = 'l';
        lastStep = 'l';
    }

    else if (lowerMid < right && lowerMid > left)
    {
        // the line is on the middle
        dir = direction::forward;
        std::cout << std::endl
                  << "FORWARD" << std::endl;
        dirLetter = 'f';
        lastStep = 'r';
    }
    else if (lowerMid < 0)
    {
        std::cout << std::endl
                  << "NOTHING" << std::endl;
        if (lastStep == 'r')
        {
            dir = direction::right;
        }
        else if (lastStep == 'l')
        {
            dir = direction::left;
        }
    }
    picResult r;
    r.direction = dir;
    std::cout << "Direction:" << r.direction << std::endl;
    return r;
}
