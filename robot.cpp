#include <iostream>
#include "robot.h"

void Robot::handle_pic(cv::VideoCapture cap)
{
    if (!cap.isOpened())
    {
        std::cout << "Cannot open the video file.\n";
    } 

    if (!cap.read(frame))
    {
        std::cout << "Failed to extract a frame.\n";
    }
    std::cout << "in handle_pic" << std::endl;
    flip(frame, frame, -1);
    frame = frame(cv::Range(320, 480), cv::Range(0, 640));
    cvtColor(frame, result,  cv::COLOR_BGR2HSV);
    const cv::Scalar lower_bound = cv::Scalar(80, 80, 80);
    const cv::Scalar higher_bound = cv::Scalar(195, 255, 255);
    cv::inRange(result, lower_bound, higher_bound, result);
    cv::bitwise_not(result, result);
	//cv::Point p1(160, middle), p2(0,middle2);
	//cv::line(bnw, p1, p2, cv::Scalar(255, 0, 0), 2, cv::LINE_4);
    if (frame.empty())
    {
	std::cout << "Could not open or find the image!\n";
    }
    std::cout << "handle_pic out" <<std::endl;

}

enum direction
{
    err,
    left,
    right
};

picResult Robot::find_direction()
{
	std::cout << "in find_direction" << std::endl;
    int rows = result.rows;
    int cols = result.cols;
    long sumOfLine1 = 0;
    long line_lenght = 0;
    for (int i = 0; i < cols; i++)
    {
        if (result.at<uint8_t>(rows, i) < 255)
        {
            sumOfLine1 = sumOfLine1 + i;
            line_lenght++;
        }
    }
    std::cout << "1" << std::endl;
    middle = sumOfLine1 / line_lenght;
    std::cout << "1.5" << std::endl;
    printf("%d\n", middle);
    long int sumOfLine2 = 0;
    long int line_lenght2 = 0;
    for (int i = 0; i < cols; i++)
    {
        if (result.at<uint8_t>(0, i) < 255)
        {
            sumOfLine2 = sumOfLine2 + i;
            line_lenght2++;
        }
    }
    std::cout << "2" << std::endl;
    middle2 = sumOfLine2 / line_lenght2;
    printf("%d\n", middle2);
    int angle = atan2(rows / 3, abs(middle - middle2)) * 180 / CV_PI;
    direction dir = err;
    char dirLetter = 's';
    std::cout << "3" << std::endl;
    if(angle >= 80 && angle <= 100){
	dirLetter = 'f';
    }
    else if (middle > middle2)
    {
        dir = direction::left;
	std::cout << std::endl << "LEFT" << std::endl;
	dirLetter = 'l';
        // left
    }
    else
    {
        dir = direction::right;
	std::cout << std::endl << "RIGHT" << std::endl;
	dirLetter = 'r';
        // right
    }
    picResult r;
    r.angle = angle;
    r.direction = dir;
    std::string image_path = "frames/" + std::to_string(step) + "raw" + ".jpg";
    cv::imwrite(image_path, frame);
    image_path = "frames/" + std::to_string(step) + dirLetter + ".jpg";
    cv::imwrite(image_path, result);
    std::cout << "Angle:" << r.angle << " "
         << "Direction:" << r.direction <<
	"find_direction out"<< std::endl;
    return r;
}
