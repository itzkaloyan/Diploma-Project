#include "Client.h"
#include <sys/stat.h>
#include <fstream>

int32_t GetFileSize(
	const char* filename
) {
    struct stat stat_buf;
    int rc = stat(filename, &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
    if(filename == nullptr) {
        return -1;
    }
    FILE *p_file = fopen(filename,"rb");
    if(p_file == nullptr) {
        return -2;
    }
    fseek(p_file,0,SEEK_END);
    int32_t size = ftell(p_file);
    fclose(p_file);
    return size;
}

void Client::connect(
    const std::string& port
) {
	socket.connect(port);
};

Client::~Client() {
	socket.close();
	context.close();
}

bool readFileToBuffer(
    const std::string& fileName,
    std::vector<int32_t>& output
) {
	FILE* rdFile = fopen(fileName.c_str(), "rb+");
	if (rdFile == 0) {
		Dprintf("%d file not found", 0);
		return false;
	}
	int32_t size = GetFileSize(fileName.c_str());
	if (size <=0 ) {
		Dprintf("%d size of file is below zero", size);
		return false;
	}
	if(size != output.size()) {
		output.resize(size);
	}

	fread(reinterpret_cast<char*>(&output[0]), sizeof(int32_t), size, rdFile);
	fclose(rdFile);
    if(output.empty()) {
        Dprintf("file has no contents %d", 0);
        return true;
    }
	return true;
}

const bool Client::splitAndSendPackage(
    std::vector<int32_t>& package
) {
	//TODO: add package special number
	int totalPackagesToSend = (package.size() + PackageSize - 1) / PackageSize;
	Dprintf("%d -> iterations", totalPackagesToSend);
	socket.send(zmq::buffer(package.data(), package.size() * sizeof(int32_t)),zmq::send_flags::none);
	zmq::message_t msg;
	socket.recv(msg, zmq::recv_flags::none);
	if(msg.data() == nullptr){
		Dprintf("did not recieve any message %d",0);
		return false;
	}
	Dprintf("%s", msg.to_string().c_str());
    return true;
}

const Result Client::sendCommand(
	const char* command,
	const MotionSpeed& motionSpeed
) {
	const std::string sendMsg = JsonFunction::createJsonAsString(command, motionSpeed);
	const int sizeSended = socket.send(sendMsg.data(), sendMsg.size());
	printf("message send -> %s\n", sendMsg.c_str());

	zmq::message_t msgRecv;
	socket.recv(msgRecv); // -> see if there is still a connection
	printf("%s -> recv messsage", msgRecv.to_string().c_str());
	return (sizeSended == sendMsg.size()) ? Result::Succeeded : Result::FailedToSend;
}

const Result Client::setMotorCommand(const MotionSpeed& motionSpeed) {
	return sendCommand("SetMotors", motionSpeed);
}

const Result Client::stopCommand(const MotionSpeed& motionSpeed) {
	return sendCommand("Stop", motionSpeed);
}

const Result Client::deactivate(const MotionSpeed& motionSpeed) {
	return sendCommand("Deactivate", motionSpeed);
}

const bool Client::sendHTTPFlag(
	const HTTPReq request,
	int sizeInBytes
) {
	std::string sendMsg = JsonFunction::prepareHTTPReqPost(request, sizeInBytes);
	socket.send(sendMsg.data(), sendMsg.size());
	//TODO: see how to check
	return true;
}

const Result Client::sendBuffer(
	const std::string& filename
) {
    std::vector<int32_t> output;
	if (readFileToBuffer(filename, output) == false) {
		return Result::FailedToSend;
	}
	Dprintf("the output size is --> %d", int(output.size()*sizeof(int32_t)));

	bool succeeded = sendHTTPFlag(
		HTTPReq::Post,
		output.size() * sizeof(output[0])
	);

	if (succeeded == false) {
		Dprintf("%d could not send Http flag", 0);
		return Result::FailedToSend;
	}

	zmq::message_t msg;
	socket.recv(msg); // -> see if there is still a connection
	Dprintf("%s -> recv messsage", msg.to_string().c_str());

	succeeded = splitAndSendPackage(output);
    if (succeeded == false) {
		Dprintf("%d -> could not split and send package", 0);
		return Result::FailedToSend;
	}
	return Result::Succeeded;
}
