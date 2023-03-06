#include <iostream>
#include "robot.h"

void Robot::handle_pic(cv::VideoCapture cap)
{
    if (!cap.isOpened())
    {
        std::cout << "Cannot open the video file.\n";
    } 

    if (!cap.read(frame))
    {
        std::cout << "Failed to extract a frame.\n";
    }

    flip(frame, frame, -1);
    frame = frame(cv::Range(320, 480), cv::Range(0, 640));
    cvtColor(frame, result,  cv::COLOR_BGR2HSV);
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
    right
};

picResult Robot::find_direction()
{

    int rows = result.rows;
    int cols = result.cols;
    long sumOfLine1 = 0;
    long line_lenght = 0;
    for (int i = 0; i < cols; i++)
    {
        if (result.at<uint8_t>(rows - 1, i) < 255)
        {
            sumOfLine1 = sumOfLine1 + i;
            line_lenght++;
        }
    }

    if(line_lenght != 0) {
        middle = sumOfLine1 / line_lenght;
    }
    else {
    	std::cout << "no line detected!!!" << std::endl;
    }
    printf("%d\n", middle);
    long int sumOfLine2 = 0;
    long int line_lenght2 = 0;
    for (int i = 0; i < cols; i++)
    {
        if (result.at<uint8_t>(0, i) < 255)
        {
            sumOfLine2 = sumOfLine2 + i;
            line_lenght2++;
        }
    }
    if(line_lenght2 != 0) {
        middle2 = sumOfLine2 / line_lenght2;
    }
    else {
        std::cout << "no line detected!!!" << std::endl;
    }
    printf("%d\n", middle2);
    int angle = atan2(rows, abs(middle - middle2)) * 180 / CV_PI;
    direction dir = err;
    char dirLetter = 's';
    if(angle >= 80 && angle <= 100){
	dirLetter = 'f';
    }
    else if (middle > middle2)
    {
        dir = direction::left;
	std::cout << std::endl << "LEFT" << std::endl;
	dirLetter = 'l';
    }
    else
    {
        dir = direction::right;
	std::cout << std::endl << "RIGHT" << std::endl;
	dirLetter = 'r';
    }
    picResult r;
    r.angle = angle;
    r.direction = dir;
    //cv::Point p1(320, middle2), p2(0,middle);
    //cv::line(result, p1, p2, cv::Scalar(0, 0, 0), 2, cv::LINE_4);
    //std::string image_path = "frames/" + std::to_string(step) + "raw" + ".jpg";
    //cv::imwrite(image_path, frame);
    //image_path = "frames/" + std::to_string(step) + dirLetter + ".jpg";
    //`cv::imwrite(image_path, result);
    std::cout << "Angle:" << r.angle << " "
         << "Direction:" << r.direction << std::endl;
    return r;
}
