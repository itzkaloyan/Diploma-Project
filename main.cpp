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
    obj.handle_pic(cap);
    bool startPython = false;
    int opt = 0;
    startPython = true;
    PythonScript ps(startPython);
    picResult r = obj.find_direction();
    //Movement object
    Movement move;
    std::cout << r.angle << " " << r.direction;
    if (r.angle <= 95&&r.angle >=85)
    {
	cout << "forward" << endl;
	move.forward();
    }
    else if (r.direction == 1)
    {
	cout << "left" << endl;
        move.left();
    }
    else if (r.direction == 2){
	cout << "right" << endl;
        move.right();
    }
    move.deactivate();
    return 0;
}
