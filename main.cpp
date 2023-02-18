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
    if (!cap.isOpened())
    {
        std::cout << "Cannot open the video file.\n";
        return -1;
    }

    cv::Mat frame;

    for (int frame_count = 0; frame_count < 10; frame_count++)
    {

        if (!cap.read(frame))
        {
            std::cout << "Failed to extract a frame.\n";
            return -1;
        }

        std::string image_path = "frames/" + std::to_string(frame_count) + ".jpg";
        cv::imwrite(image_path, frame);
    }
    // std::string fileName = "/home/student1/code/JetBot/HSV/test_images/light_curve_left.jpg";
    bool startPython = false;
    int opt = 0;
#ifdef _WIN32
    startPython = true;
#else
    while ((opt = getopt(argc, argv, "h:s")) != -1) {
        switch (opt) {
            case 'h':
                std::cout
                    <<"--client starts the client and connects to 127.0.0.1 on port :5555\n"
                    <<"can be used for transfering images, buffers, robot movement speed\n"
                    <<"image and buffers transfer supported for cpp Server, for now.\n"
                    <<"Movement speed supported for python server\n\n"
                    <<"--server starts the server part and connects to 127.0.0.1 on port :5555\n"
                    <<"used for transfering images and buffers, as mentioned before\n"
                    <<"client and server can be used in example main\n, to run it enable STAND_ALONE in cppClientLib/CMakeLists.txt\n"
                    <<"here only --startPython can be used, to start the server on new thread, with no need to run the script from new terminal\n";
                exit(0);
            case 's':
                startPython = true;
                break;
            default:
                printf("could not recognize command line argv!\nsupported args are -> \n--client\n--server\n");
                exit(-1);
        }
    }
#endif
    PythonScript ps(startPython);
    MotionSpeed speed(0.3f, 0.3f);
    Client client;
    client.connect("tcp://127.0.0.1:5555");
    Robot obj;
    obj.handle_pic(frame);
    obj.find_direction();
    picResult r;
    std::cout << r.angle << " " << r.direction;
    Movement move;
    if (r.angle <= 95&&r.angle >=85)
    {
	//move.forward();
	for (int i = 0; i < 1000; i++) {
        const Result res = client.setMotorCommand(speed);
        if (res == Result::FailedToSend) {
            printf("failed to send\n");
            break;
        }
        }
    }
    else if (r.direction == 1)
    {
        // Movement::left();
	//MotionSpeed speed (-0,3f, 0,3f);
	for (int i = 0; i < 1000; i++) {
		const Result res = client.setMotorCommand(speed);
		if (res == Result::FailedToSend) {
			printf("failed to send left\n");
		break;
	}
	}
    }
    else if (r.direction == 2){
	   // MotionSpeed speed (0,3f,-0,3f);
	    for (int i = 0; i < 1000; i++) {
		const Result res = client.setMotorCommand(speed);
		if (res == Result::FailedToSend) {
			printf("failed to send right\n");
			break;
		}
	    }
         // Movement::left();
    }
    else if (r.direction == -1)
    {
        // Movement::stop()
    }
    client.stopCommand();
    client.disconnect();
    return 0;
}
