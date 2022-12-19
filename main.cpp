#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{

    Mat image = imread("../rose.jpg",
                       IMREAD_COLOR);

    if (image.empty())
    {
        cout << "Image File "
             << "Not Found" << endl;

        cin.get();
        return -1;
    }

    imshow("Window Name", image);

    waitKey(0);
    return 0;
}