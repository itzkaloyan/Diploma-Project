#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "findContours.h"
using namespace cv;
using namespace std;

void ContourFinder::find(Mat src_gray)
{
    Mat canny_output;
    Canny(src_gray, canny_output, thresh, thresh * 2);
    findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
}