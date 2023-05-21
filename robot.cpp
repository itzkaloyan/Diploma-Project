#include <iostream>
#include "robot.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <memory>
#include <chrono>
using json = nlohmann::json;
using namespace std::chrono;

void Robot::handle_pic(const cv::Mat &inframe)
{
    auto start = high_resolution_clock::now();
    flip(inframe, frame, -1);
    frame = frame(cv::Range(239, 240), cv::Range(0, 320));
    cvtColor(frame, result, cv::COLOR_BGR2HSV);
    const cv::Scalar lower_bound = cv::Scalar(80, 80, 80);
    const cv::Scalar higher_bound = cv::Scalar(195, 255, 255);
    cv::inRange(result, lower_bound, higher_bound, result);
    cv::bitwise_not(result, result);
    if (frame.empty())
    {
        std::cout << "Could not open or find the image!\n";
    }
    auto stop = high_resolution_clock::now(); // Get stop time
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "handle_pic: " << duration.count() << " microseconds" << std::endl;
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
    auto start = high_resolution_clock::now();
    int rows = result.rows;
    int cols = result.cols;
    // lower
    long sumOfBottom = 0;
    long lengthOfBottom = 0;
    int lowerMid = -1;
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
    printf("lowerMid: %ld\n", lowerMid);
    direction dir = err;
    std::ifstream ifs("../config.json");
    json j = json::parse(ifs);
    float left = j["left"];
    float right = j["right"];
    std::cout << " left = " << left << std::endl;
    left = left * cols;
    right = right * cols;

    if (lowerMid >= right)
    {
        // the line is on the right
        dir = direction::right;
        std::cout << std::endl
                  << "RIGHT" << std::endl;
        lastStep = 'r';
    }
    else if (lowerMid <= left && lowerMid >= 0)
    {
        // the line is on the left
        dir = direction::left;
        std::cout << std::endl
                  << "LEFT" << std::endl;
        lastStep = 'l';
    }

    else if (lowerMid < right && lowerMid > left)
    {
        // the line is on the middle
        dir = direction::forward;
        std::cout << std::endl
                  << "FORWARD" << std::endl;
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
    // std::string image_path = "frames/" + "shot.jpg";
    // cv::imwrite(image_path, result);
    std::cout << "Direction:" << r.direction << std::endl;
    auto stop = high_resolution_clock::now(); // Get stop time
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "find_direction: " << duration.count() << " microseconds" << std::endl;
    return r;
}
