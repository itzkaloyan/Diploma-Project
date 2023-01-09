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
        cout << "Width : " << src.size().width << endl;
        cout << "Height: " << src.size().height << endl;
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
    const char *result = "Result";
    namedWindow(result);
    imshow(result, bnl);
    waitKey();
    return 0;
}
