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
using namespace cv;
using namespace std;

void executeFunction(const char* exec) {
    system(exec);
}
struct PythonScript {
    PythonScript(const bool usePython) {
        this->usePython = usePython;
        const char* exec = "python ../python/Server.py";
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
    cv::VideoCapture cap(CAP_V4L2);
    cv::Mat frame;
    Robot obj;
    Movement move;
    bool startPython = false;
    int opt = 0;
    startPython = true;
    PythonScript ps(startPython);
    for (int step = 0; step < 10; step++)
    {
        obj.handle_pic(cap, step);
        picResult r = obj.find_direction();
        move.moving(r);
        sleep(3);
    }
    move.deactivate();
    return 0;
}
