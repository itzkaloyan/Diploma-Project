
#include <cstdlib>
#include <thread>
#include <iostream>
#include <unistd.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <string>
#include "robot.h"
#ifndef PC
#include "movement.h"
#include "Client.h"
#endif

void executeFunction(const char *exec)
{
    system(exec);
}
struct PythonScript
{
    PythonScript(const bool usePython)
    {
        this->usePython = usePython;
        const char *exec = "python ../../Diploma-Project/python/Server.py";
        if (usePython)
        {
            tr = std::thread(&executeFunction, exec);
        }
    }
    ~PythonScript()
    {
        if (usePython)
        {
            tr.join();
        }
    }

private:
    std::thread tr;
    bool usePython = false;
};

int main(int argc, char **argv)
{
    Robot obj;

#ifndef PC
    Movement move;
    bool startPython = false;
    int opt = 0;
    startPython = true;
    PythonScript ps(startPython);
    std::cout << "started server" << std::endl;
 //   sleep(10);
    cv::VideoCapture cap(cv::CAP_V4L2);

    if (cap.isOpened())
    {
        printf("Opened video file.\n");
    }
    else
    {
        std::cout << "Cannot open the video file.\n";
    }
#endif
    while (obj.getStep() <= 200)
    {
        int step = obj.getStep();
        printf("step: %d\n", step);
        obj.setStep(step + 1);

#ifdef PC
        cv::Mat frame = cv::imread("7f.jpg");
#else
        cv::Mat frame;
        if (cap.read(frame))
	{
		printf("read frame\n");
	}
	else
        {
            std::cout << "Failed to extract a frame.\n";
        }
#endif

        obj.handle_pic(frame);
        picResult r = obj.find_direction();

#ifndef PC
        move.controller(r);
#endif
        usleep(10000);
        std::cout << std::endl
                  << obj.getStep() << std::endl;
    }
#ifndef PC
    move.deactivate();
#endif
    return 0;
}
