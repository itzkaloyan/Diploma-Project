#pragma once
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

struct contour
{
    contour() = default;
    void thresh_callback();

private:
    int thresh = 100;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
};
