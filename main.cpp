#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    int Hue_Lower_Value = 100;
    int Hue_Lower_Upper_Value = 140;
    int Saturation_Lower_Value = 150;
    int Saturation_Upper_Value = 255;
    int Value_Lower = 0;
    int Value_Upper = 255;
    Mat image = imread("../bluePowder.jpeg",
                       IMREAD_COLOR);

    if (image.empty())
    {
        cout << "Image File "
             << "Not Found" << endl;

        cin.get();
        return -1;
    }

    Mat hsv;
    cvtColor(image, hsv, COLOR_BGR2HSV);

    imshow("Original", image);

    Mat detection_screen;

    inRange(hsv, Scalar(Hue_Lower_Value, Saturation_Lower_Value, Value_Lower), Scalar(Hue_Lower_Upper_Value, Saturation_Upper_Value, Value_Upper), detection_screen);
    imshow("Result", detection_screen);
    waitKey(0);
    return 0;
}