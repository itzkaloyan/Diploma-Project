#include "Client.h"
#include <cstdlib>
#include <thread>
#include <iostream>
#include <unistd.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <string>
#include "robot.h"
#include "movement.h"

void executeFunction(const char* exec) {
    system(exec);
}
struct PythonScript {
    PythonScript(const bool usePython) {
        this->usePython = usePython;
        const char* exec = "python ../../Diploma-Project/python/Server.py";
        if(usePython) {
            tr = std::thread(&executeFunction, exec);
        }
    }
    ~PythonScript() {
        if(usePython) {
            tr.join();
        }
    }
private:
    std::thread tr;
    bool usePython = false;
};

int main(int argc, char** argv) {
    Robot obj;
    Movement move;
    bool startPython = false;
    int opt = 0;
    startPython = true;
    PythonScript ps(startPython);
    std::cout << "started server" << std::endl;
    sleep(10);
    cv::VideoCapture cap(cv::CAP_V4L2);
    cv::Mat frame;
    while (obj.getStep() <= 10)
    {
	obj.setStep(obj.getStep()+1);
        obj.handle_pic(cap);
        picResult r = obj.find_direction();
        move.controller(r);
        usleep(10000);
    }
    move.deactivate();
    return 0;
}
