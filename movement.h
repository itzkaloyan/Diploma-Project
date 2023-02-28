#pragma once
#include "Client.h"
#include "robot.h"

struct Movement
{
    Movement()
    {
	std::cout << " ok " << std::endl;
        client.connect("tcp://127.0.0.1:5555");
    }
    void forward();
    void right();
    void left();
    void deactivate();
    void controller(picResult r);
	
private:
    Client client;
    float motorSpeed = 0.4;
};
