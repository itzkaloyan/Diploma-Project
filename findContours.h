#pragma once
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

struct ContourFinder
{
    ContourFinder() = default;
    void find(Mat src_gray);

private:
    int thresh = 100;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
};
