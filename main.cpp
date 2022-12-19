#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    printf("OpenCV: %s", cv::getBuildInformation().c_str());
    return 0;
}