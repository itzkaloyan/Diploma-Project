#pragma once
#include "../cppzmq/zmq.hpp"
#include "depend.h"
#include "Json.h"

class Client
{
	const bool splitAndSendPackage(
		std::vector<int32_t>& package
	);
	const bool sendHTTPFlag(
		const HTTPReq request,
		int sizeInBytes
	);
	const Result sendCommand(
		const char* command,
		const MotionSpeed& motionSpeed
	);
	const Result sendBuffer(
		const std::string& filename
	);
public:
	Client() = default;
	Client(Client& other) = delete;
	Client(Client&& other) = delete;
	Client operator=(Client& other) = delete;
	Client& operator=(Client&& other) = delete;
	void connect(
		const std::string& port
	);
	const Result setMotorCommand(const MotionSpeed& motionSpeed);
	const Result stopCommand(const MotionSpeed& motionSpeed);
	const Result deactivate(const MotionSpeed& motionSpeed);
	~Client();
private:
	zmq::context_t context{ 1 };
	zmq::socket_t socket{ context, zmq::socket_type::req };
};
