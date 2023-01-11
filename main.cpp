#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "findContours.h"
using namespace cv;
using namespace std;

int handle_pic(Mat &src, char **argv)
{
    src = imread("../curve_right_iphone.jpg");
    if (src.empty())
    {
        cout << "Could not open or find the image!\n"
             << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }
    else
    {
        // cout << "Width : " << src.size().width << endl;
        // cout << "Height: " << src.size().height << endl;
        src = src(Range(0, 629), Range(0, 800));
        return 0;
    }
}
int main(int argc, char **argv)
{
    Mat src;
    handle_pic(src, argv);
    ContourFinder obj;
    Mat src_gray;
    Mat bnl;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));
    // obj.find(src_gray);
    threshold(src_gray, bnl, 127, 255, THRESH_BINARY);
    int rows = src_gray.rows;
    int cols = src_gray.cols;
    int sumOfLine1 = 0;
    int line_lenght = 0;
    for (int i = 0; i < cols; i++)
    {
        if (bnl.at<uint8_t>(rows - 1, i) < 255)
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
        if (bnl.at<uint8_t>((rows / 3) * 2, i) < 255)
        {
            sumOfLine2 = sumOfLine2 + i;
            line_lenght2++;
        }
    }
    int middle2 = 0;
    middle2 = sumOfLine2 / line_lenght2;
    printf("%d\n", middle2);
    int angle = atan2(rows / 3, abs(middle - middle2)) * 180 / CV_PI;
    int direction = -1;
    if (middle > middle2)
    {
        direction = 0;
        // left
    }
    else
    {
        direction = 1;
        // right
    }
    printf("Angle:"
           "%d\n",
           angle);
    const char *result = "Result";
    namedWindow(result);
    imshow(result, bnl);
    waitKey();
    return 0;
}
