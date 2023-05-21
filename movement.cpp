#include <iostream>
#include "movement.h"
#include "robot.h"
#include <unistd.h>

void Movement::left()
{
    MotionSpeed ms(-0.16f, -0.16f);
    client.setMotorCommand(ms);
}

void Movement::right()
{
    MotionSpeed ms(0.16f, 0.16f);
    client.setMotorCommand(ms);
}

void Movement::forward()
{
    MotionSpeed ms(0.24f, -0.24f);
    client.setMotorCommand(ms);
}

void Movement::stop()
{
    MotionSpeed ms(0.0f, 0.0f);
    client.setMotorCommand(ms);
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
        break;

    case 2:
        std::cout << "right" << std::endl;
        right();
        break;

    case 3:
        std::cout << "forward" << std::endl;
        forward();
        break;

    default:
        stop();
    }
}
