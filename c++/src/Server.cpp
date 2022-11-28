#include "Server.h"
#include "Json.h"

Server::Server(
	Server&& other
) noexcept {
	std::swap(*this, other);
}

Server::~Server() {
	socket.close();
	context.close();
}

Server& Server::operator=(
	Server&& other
) noexcept {
	if (this != &other)
	{
		std::swap(*this, other);
	}
	return *this;
}

void Server::bind(
	const std::string& port
) {
	socket.bind(port);
}

bool Server::catchPostRequest(
	std::vector<int32_t>& tensor, //vector to be filled with data
	const int size // size in bytes
) {
	tensor.resize(size);
	zmq::recv_result_t result = socket.recv(tensor.data(), size);
	if (result.has_value() == false) {
		Dprintf("was not able to recv data %d", 0);
		return false;
	}

	result = socket.send(zmq::buffer("recieved data"), zmq::send_flags::none);
	if (result.value() == false) {
		Dprintf("was not able to recv data %d", int(result.value()));
		return false;
	}
	return true;
}

const bool Server::listenForCommand() {
	zmq::message_t msg;
	JsonRequests request = JsonRequests::Invalid;
	bool res = socket.recv(&msg);
	if (res == false) {
		printf("could not recieve from client\n");
		return false;
	}
	res = JsonFunction::getJsonRequest(
		msg.to_string(),
	 	request
	);
	if (res == false) {
		socket.send(zmq::buffer("closing the gate"), zmq::send_flags::dontwait);
		return false;
	}
	printf("%s", msg.to_string().c_str());
	socket.send(zmq::buffer("recieved function"), zmq::send_flags::dontwait);
	return true;
}

void Server::listen() {
	zmq::message_t msg;
	int32_t sizeOfIncommingBuffer;
	HTTPReq request = HTTPReq::None;

	socket.recv(&msg);
	int sizeOfBufferInBytes = JsonFunction::getReqAndSize(
		msg.to_string(),
	 	request
	);

	Dprintf("message is %s",msg.to_string().c_str());
	if (sizeOfBufferInBytes == -1) {
		return;
	}
	socket.send(zmq::buffer("recieved size in bytes, catching post request"), zmq::send_flags::dontwait);
	std::vector<int32_t> tensor;
	bool succeeded = catchPostRequest(tensor, sizeOfBufferInBytes);
	if (succeeded == false) {
		Dprintf("could was not able to recv message, aborting with %d", -1);
		exit(-1);
	}
	Dprintf("tensor's first element %d", tensor[0]);
}
