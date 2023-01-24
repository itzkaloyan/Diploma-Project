#include <iostream>
#include "movement.h"

void Movement::left()
{
    ms = MotionSpeed{-0.9, -0.9f};
    client.setMotorCommand(ms);
    ms = MotionSpeed{0.0, 0.0f};
    client.setMotorCommand(ms);
}

void Movement::right()
{
    ms = MotionSpeed{0.9, 0.9f};
    client.setMotorCommand(ms);
    ms = MotionSpeed{0.0, 0.0f};
    client.setMotorCommand(ms);
}

void Movement::forward()
{
    ms = MotionSpeed{0.9, -0.9f};
    client.setMotorCommand(ms);
    ms = MotionSpeed{0.0, 0.0f};
    client.setMotorCommand(ms);
}

void Movement::stop()
{
    ms = MotionSpeed{0.0, 0.0f};
    client.stopCommand(ms);
}

void Movement::deactivate()
{
    client.deactivate(ms);
}
