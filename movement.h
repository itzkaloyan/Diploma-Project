#pragma once
#include "Client.h"
#include <opencv2/opencv.hpp>
#include <iostream>

struct Movement
{
    Movement()
    {
        cout << " ok " << endl;
        client.connect("tcp://127.0.0.1:5555");
    }
    int direction();
    void forward();
    void right();
    void left();
    void stop();
    void deactivate();

private:
    MotionSpeed ms(0.0, 0.0f);
};