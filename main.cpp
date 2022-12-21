#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "findContours.h"
using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat src = imread("../curve_left_iphone.jpg");
    if (src.empty())
    {
        cout << "Could not open or find the image!\n"
             << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }
    contour obj;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));
    const char *source_window = "Source";
    namedWindow(source_window);
    imshow(source_window, src);
    const int max_thresh = 255;
    createTrackbar("Canny thresh:", source_window, &thresh, max_thresh, obj.thresh_callback());
    obj.thresh_callback();
    waitKey();
    return 0;
}
