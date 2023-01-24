#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <string>
#include "robot.h"
#include "movement.h"
using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    std::string fileName = "/home/student1/code/JetBot/HSV/test_images/curve_right_iphone.jpg";
    Robot obj;
    Movement move;
    obj.handle_pic(fileName);
    obj.find_direction();
    const char *result = "Result";
    namedWindow(result);
    imshow(result, obj.getBnw());
    waitKey();
    return 0;
}
