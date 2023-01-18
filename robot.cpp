#include <iostream>
#include "robot.h"

using namespace cv;
using namespace std;

Mat Robot::handle_pic(std::string imageFile)
{
    Mat src = imread(imageFile);
    if (src.empty())
    {
        cout << "Could not open or find the image!\n";
        return Mat();
    }
    else
    {
        // cout << "Width : " << src.size().width << endl;
        // cout << "Height: " << src.size().height << endl;
        src = src(Range(0, 629), Range(0, 800));
    }
    Mat src_gray;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));
    threshold(src_gray, bnw, 127, 255, THRESH_BINARY);
    return bnw;
}

enum direction
{
    err,
    left,
    right
};

Result Robot::find_direction()
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
    Result r;
    r.angle = angle;
    r.direction = dir;
    cout << "Angle:" << r.angle << " "
         << "Direction:" << r.direction << endl;
    return r;
}