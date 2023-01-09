#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "findContours.h"
using namespace cv;
using namespace std;

int handle_pic(Mat &src, char **argv)
{
    src = imread("../curve_left_iphone.jpg");
    if (src.empty())
    {
        cout << "Could not open or find the image!\n"
             << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }
    else
    {
        return 0;
    }
}
int main(int argc, char **argv)
{
    Mat src;
    handle_pic(src, argv);
    ContourFinder obj;
    Mat src_gray;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));
    obj.find(src_gray);
    return 0;
}
