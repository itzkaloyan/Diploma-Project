#include <iostream>
#include "movement.h"
#include "robot.h"
#include <unistd.h>

void Movement::left()
{
    MotionSpeed ms;
    ms = MotionSpeed{-motorSpeed, -motorSpeed};
    client.setMotorCommand(ms);
    usleep(10000);
    client.stopCommand();
}

void Movement::right()
{
    MotionSpeed ms;
    ms = MotionSpeed{motorSpeed, motorSpeed};
    client.setMotorCommand(ms);
    usleep(10000);
    client.stopCommand();
}

void Movement::forward()
{
    MotionSpeed ms;
    ms = MotionSpeed{motorSpeed, -motorSpeed};
    client.setMotorCommand(ms);
    usleep(10000);
    client.stopCommand();
}

void Movement::stop()
{
    MotionSpeed ms;
    ms = MotionSpeed{0, 0};
    client.setMotorCommand(ms);
    usleep(10000);
    client.stopCommand();
}

void Movement::deactivate()
{
    client.disconnect();
}

void Movement::controller(picResult r)
{
    switch (r.direction)
    {
    case 1:
        std::cout << "left" << std::endl;
        left();
    case 2:
        std::cout << "right" << std::endl;
        right();
    case 3:
        std::cout << "forward" << std::endl;
        forward();
    default:
        stop();
    }
}
