#include <iostream>
#include "robot.h"

using namespace cv;
using namespace std;

Mat Robot::handle_pic(cv::Mat frame)
{
	Mat flipped;
    if (frame.empty())
    {
        cout << "Could not open or find the image!\n";
        return Mat();
    }
    else
    {
        cout << "in!" << endl;
        // cout << "Height: " << src.size().height << endl;
        //frame = frame(Range(0, 629), Range(0, 800));
	//cv::flip(frame, flipped, 0);
    }
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    blur(gray, flipped, Size(3, 3));
    threshold(flipped, bnw, 127, 255, THRESH_BINARY);
    return bnw;
    cout << "out!" << endl;
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
    cout << "Angle:" << r.angle << " "
         << "Direction:" << r.direction << endl;
    return r;
}
