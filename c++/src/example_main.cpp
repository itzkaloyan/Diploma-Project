#include "../cppzmq/zmq.hpp"
#include "Client.h"
#include "Server.h"

int main(int argc, char** argv)
{
	if (argc == 1) {
		printf("no argvs passed\n");
		Client client;
		const Result (Client::*functPonter[])(const MotionSpeed&) = {
			&Client::backwardCommand,
			&Client::forewardCommand,
			&Client::leftCommand,
			&Client::rightCommand,
			&Client::stopCommand,
			&Client::setMotorCommand,
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
	std::string arg = argv[1];
	Dprintf("arg = %s", arg.c_str());
	if (arg == "--client") {
		Client client;
		client.connect("tcp://127.0.0.1:5555");
		client.sendBuffer("something.txt");
	} else if (arg == "--server") {
		Server server;
		server.bind("tcp://127.0.0.1:5555");
		while(server.listenForCommand()) {}
	} else {
		printf("could not recognize command line argv!\nsupported args are -> \n--client\n--server\n");
		return -1;
	}
	return 0;
}
