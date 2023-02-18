#include <iostream>
#include "movement.h"
//#include "robot.h"
#include <unistd.h>

void Movement::left()
{
    auto ms = MotionSpeed{-0.3, -0.3f};
    client.setMotorCommand(ms);
    usleep(50650);
    ms = MotionSpeed{0.0, 0.0f};
    client.setMotorCommand(ms);
}

void Movement::right()
{
    auto ms = MotionSpeed{0.3, 0.3f};
    client.setMotorCommand(ms);
    usleep(50650);
    ms = MotionSpeed{0.0, 0.0f};
    client.setMotorCommand(ms);
}

void Movement::forward()
{
    auto ms = MotionSpeed{0.3, -0.3f};
    client.setMotorCommand(ms);
    usleep(50650);
    ms = MotionSpeed{0.0, 0.0f};
    client.setMotorCommand(ms);
}
