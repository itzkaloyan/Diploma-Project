#include "Client.h"

int main(int argc, char** argv)
{
    Client client;
    const Result (Client::*functPonter[])(const MotionSpeed&) = {
        &Client::setMotorCommand,
        &Client::stopCommand,
        &Client::deactivate
    };
    client.connect("tcp://127.0.0.1:5555");
    for (int i = 0; i < 7; i++) {
        const Result res = (client.*functPonter[i])(MotionSpeed{0.5, 1.0f});
        if (res == Result::FailedToSend) {
            printf("failed to send\n");
        }
    }
    return 0;
}