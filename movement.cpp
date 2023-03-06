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

void Movement::deactivate()
{
	client.disconnect();
}

void Movement::controller(picResult r)
{
    std::cout << r.angle << " " << r.direction;
    if (r.angle <= 100&&r.angle >=80)
    {
	std::cout << "forward" << std::endl;
	forward();
    }
    else if (r.direction == 1)
    {
	std::cout << "left" << std::endl;
        left();
    }
    else if (r.direction == 2)
    {
	std::cout << "right" << std::endl;
        right();
    }
}

