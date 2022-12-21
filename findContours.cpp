#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "findContours.h"
using namespace cv;
using namespace std;

void contour::thresh_callback()
{
    Mat src_gray;
    Mat canny_output;
    RNG rng(12345);
    Canny(src_gray, canny_output, thresh, thresh * 2);
    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    for (size_t i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
    }
    imshow("Contours", drawing);
}