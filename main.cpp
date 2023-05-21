#include <cstdlib>
#include <thread>
#include <iostream>
#include <unistd.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <string>
#include "robot.h"
#include <chrono>
#ifndef PC
#include "movement.h"
#include "Client.h"
#endif
using namespace std::chrono;

void run();
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

int main()
{
#ifndef PC
    bool startPython = false;
    int opt = 0;
    startPython = true;
    PythonScript ps(startPython);
    std::cout << "started server" << std::endl;
    sleep(5);
    run();
    return 0;
}
#endif
void run()
{
    Robot obj;

    cv::VideoCapture cap(cv::CAP_V4L2);

    if (cap.isOpened())
    {
        printf("Opened video file.\n");
    }
    else
    {
        std::cout << "Cannot open the video file.\n";
    }
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 320);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 240);
    Movement move;
    while (obj.getStep() <= 2000)
    {
        auto start = high_resolution_clock::now();
        int step = obj.getStep();
        printf("step: %d\n", step - 1);
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
        std::cout << std::endl
                  << obj.getStep() << std::endl;
        auto stop = high_resolution_clock::now(); // Get stop time
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "run(): " << duration.count() << " microseconds" << std::endl;
    }
#ifndef PC
    move.stop();
    move.deactivate();
#endif
}
