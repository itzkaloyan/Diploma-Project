#include <iostream>
#include "robot.h"

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

    // // upper
    // long sumOfTop = 0;
    // long lengthOfTop = 0;
    // upperMid = 0;
    // for (int i = 0; i < cols; i++)
    // {
    //     if (result.at<uint8_t>(0, i) < 255)
    //     {
    //         sumOfTop = sumOfTop + i;
    //         lengthOfTop++;
    //     }
    // }
    // printf("%d\n", upperMid);
    // int angle = 0;
    // if (lengthOfTop != 0)
    // {
    //     upperMid = sumOfTop / lengthOfTop;
    //     angle = atan2((rows - 1) - 0, (lowerMid - upperMid)) * 180 / CV_PI;
    // }
    // else
    // {

    //     // right
    //     long sumOfRight = 0;
    //     long lengthOfRight = 0;
    //     rightMid = 0;    // else
    // {

    //     // right
    //     long sumOfRight = 0;
    //     long lengthOfRight = 0;
    //     rightMid = 0;
    //     for (int i = 0; i < rows; i++)
    //     {
    //         if (result.at<uint8_t>(i, 0) < 255)
    //         {
    //             sumOfRight = sumOfRight + i;
    //             lengthOfRight++;
    //         }
    //     }
    //     if (lengthOfRight != 0)
    //     {
    //         rightMid = sumOfRight / lengthOfRight;
    //         angle = atan2((rows - 1) - rightMid, lowerMid - (cols - 1)) * 180 / CV_PI;
    //     }
    //     // left
    //     long sumOfLeft = 0;
    //     long lengthOfLeft = 0;
    //     leftMid = 0;
    //     for (int i = 0; i < rows; i++)
    //     {
    //         if (result.at<uint8_t>(i, cols - 1) < 255)
    //         {
    //             sumOfLeft = sumOfLeft + i;
    //             lengthOfLeft++;
    //         }
    //     }
    //     if (lengthOfLeft != 0)
    //     {
    //         leftMid = sumOfLeft / lengthOfLeft;
    //         angle = atan2((rows - 1) - leftMid, 0) * 180 / CV_PI;
    //     }
    // }
    //     {
    //         if (result.at<uint8_t>(i, 0) < 255)
    //         {
    //             sumOfRight = sumOfRight + i;
    //             lengthOfRight++;
    //         }
    //     }
    //     if (lengthOfRight != 0)
    //     {
    //         rightMid = sumOfRight / lengthOfRight;
    //         angle = atan2((rows - 1) - rightMid, lowerMid - (cols - 1)) * 180 / CV_PI;
    //     }
    //     // left
    //     long sumOfLeft = 0;
    //     long lengthOfLeft = 0;
    //     leftMid = 0;
    //     for (int i = 0; i < rows; i++)
    //     {
    //         if (result.at<uint8_t>(i, cols - 1) < 255)
    //         {
    //             sumOfLeft = sumOfLeft + i;
    //             lengthOfLeft++;
    //         }
    //     }
    //     if (lengthOfLeft != 0)
    //     {
    //         leftMid = sumOfLeft / lengthOfLeft;
    //         angle = atan2((rows - 1) - leftMid, 0) * 180 / CV_PI;
    //     }
    // }
    // angle = abs(angle);
    // int angle = 0;
    direction dir = err;
    char dirLetter = 's';
    const int left = cols * 0.32;
    const int right = cols * 0.67;
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
    // r.angle = angle;
    r.direction = dir;
    // cv::Point p1(320, middle2), p2(0,middle);
    // cv::line(result, p1, p2, cv::Scalar(0, 0, 0), 2, cv::LINE_4);
    // std::string image_path = "frames/" + std::to_string(step) + "raw" + ".jpg";
    // cv::imwrite(image_path, frame);
    // std::string image_path = "frames/" + std::to_string(step) + dirLetter + ".jpg";
    // cv::imwrite(image_path, result);
    std::cout //<< "Angle:" << r.angle << " "
        << "Direction:" << r.direction << std::endl;
    return r;
}
