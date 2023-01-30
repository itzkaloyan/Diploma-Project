#include <iostream>
#include "movement.h"
//#include "robot.h"
#include <unistd.h>

void Movement::left()
{
    auto ms = MotionSpeed{-0.3, -0.3f};
    client.setMotorCommand(ms);
    usleep(14450);
    ms = MotionSpeed{0.0, 0.0f};
    client.setMotorCommand(ms);
}

void Movement::right()
{
    auto ms = MotionSpeed{0.9, 0.9f};
    client.setMotorCommand(ms);
    ms = MotionSpeed{0.0, 0.0f};
    client.setMotorCommand(ms);
}

void Movement::forward()
{
    auto ms = MotionSpeed{0.9, -0.9f};
    client.setMotorCommand(ms);
    ms = MotionSpeed{0.0, 0.0f};
    client.setMotorCommand(ms);
}

void Movement::stop()
{
    auto ms = MotionSpeed{0.0, 0.0f};
    client.stopCommand(ms);
}

void Movement::deactivate()
{
    auto ms = MotionSpeed{0.0, 0.0f};
    client.deactivate(ms);
}
