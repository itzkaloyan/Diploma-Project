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
    int rows = src_gray.rows;
    int cols = src_gray.cols;
    // for (int i = 0; i <= rows; i++)
    // {
    //     for (int j = 0; j <= cols; j++)
    //     {
    //         cout << ".";
    //     }
    // }
    // const char *result = "Result";
    // namedWindow(result);
    // imshow(result, canny_output);
    // waitKey();
}