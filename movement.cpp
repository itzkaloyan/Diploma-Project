#include <iostream>
#include "movement.h"
#include "robot.h"
#include <unistd.h>

void Movement::left()
{
    MotionSpeed ms(-0.4f, -0.4f);
    client.setMotorCommand(ms);
    usleep(15000);
    client.stopCommand();
}

void Movement::right()
{
    MotionSpeed ms(0.4f, 0.4f);
    client.setMotorCommand(ms);
    usleep(15000);
    client.stopCommand();
}

void Movement::forward()
{
    MotionSpeed ms(0.4f, -0.4f);
    client.setMotorCommand(ms);
    usleep(40000);
    client.stopCommand();
}

void Movement::stop()
{
    MotionSpeed ms;
    ms = MotionSpeed{0.0f, 0.0f};
    client.setMotorCommand(ms);
    usleep(40000);
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
    case 2:
        std::cout << "right" << std::endl;
        right();
        break;
    case 1:
        std::cout << "left" << std::endl;
        left();
        break;

    case 3:
        std::cout << "forward" << std::endl;
        forward();
        break;
    default:
        stop();
    }
}
