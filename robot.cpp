#include <iostream>
#include "robot.h"

void Robot::handle_pic(cv::VideoCapture cap)
{
    if (!cap.isOpened())
    {
        std::cout << "Cannot open the video file.\n";
    } 
    cv::Mat frame;

    for (int frame_count = 0; frame_count < 10; frame_count++)
    {

        if (!cap.read(frame))
        {
            std::cout << "Failed to extract a frame.\n";
        }
        //frame = frame(Range(0, 629), Range(0, 800));
        flip(frame, frame, -1);
        cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
        blur(frame, frame, cv::Size(3, 3));
        threshold(frame, bnw, 210, 255, cv::THRESH_BINARY);
        std::string image_path = "frames/" + std::to_string(frame_count) + ".jpg";
        cv::imwrite(image_path, frame);
    }

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
    int rows = bnw.rows;
    int cols = bnw.cols;
    int sumOfLine1 = 0;
    int line_lenght = 0;
    for (int i = 0; i < cols; i++)
    {
        if (bnw.at<uint8_t>(rows - 1, i) < 255)
        {
            sumOfLine1 = sumOfLine1 + i;
            line_lenght++;
        }
    }
    int middle = 0;
    middle = sumOfLine1 / line_lenght;
    printf("%d\n", middle);
    int sumOfLine2 = 0;
    int line_lenght2 = 0;
    for (int i = 0; i < cols; i++)
    {
        if (bnw.at<uint8_t>((rows / 3) * 2, i) < 255)
        {
            sumOfLine2 = sumOfLine2 + i;
            line_lenght2++;
        }
    }
    int middle2 = 0;
    middle2 = sumOfLine2 / line_lenght2;
    printf("%d\n", middle2);
    int angle = atan2(rows / 3, abs(middle - middle2)) * 180 / CV_PI;
    direction dir = err;
    if (middle > middle2)
    {
        dir = direction::left;
        // left
    }
    else
    {
        dir = direction::right;
        // right
    }
    picResult r;
    r.angle = angle;
    r.direction = dir;
    std::cout << "Angle:" << r.angle << " "
         << "Direction:" << r.direction << std::endl;
    return r;
}
