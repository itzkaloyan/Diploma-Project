#include <iostream>
#include "movement.h"
//#include "robot.h"
#include <unistd.h>

void Movement::left()
{
    MotionSpeed ms;
    ms = MotionSpeed{-motorSpeed, -motorSpeed};
    client.setMotorCommand(ms);
    sleep(1);
    client.stopCommand();
}

void Movement::right()
{
    MotionSpeed ms;
    ms = MotionSpeed{motorSpeed, motorSpeed};
    client.setMotorCommand(ms);
    sleep(1);
    client.stopCommand();
}

void Movement::forward()
{
    MotionSpeed ms;
    ms = MotionSpeed{motorSpeed, -motorSpeed};
    client.setMotorCommand(ms);
    sleep(1);
    client.stopCommand();
}
void Movement::deactivate()
{
	client.disconnect();
}
