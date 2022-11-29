#include "Json.h"
#include "json.hpp"

MotionSpeed::MotionSpeed(
	const float primary,
	const float secondaryMotion
) {
	this->primaryMotion = primary;
	this->secondMotion = secondaryMotion;
}

const bool MotionSpeed::isSingleMotion() const {
	static const float minMovement = 0.01f;
	bool secMotion = secondMotion <= minMovement;
	return secMotion;
}

const std::string JsonFunction::createJsonAsString(
	const char* function,
	const MotionSpeed& motionSpeed
) {
	const std::string req(function);
	nlohmann::json json;
	if (req == "SetMotors") {
		if(motionSpeed.isSingleMotion()) {
			printf("cannot set motion if Motion Speed does not have secondary motion set\n");
			return "";
		}
		json[req] = {motionSpeed.primaryMotion, motionSpeed.secondMotion};
	} else {
		json[req] = motionSpeed.primaryMotion;
	}
	return json.dump();
}

const std::string JsonFunction::prepareHTTPReqPost(HTTPReq request, int sizeToSendInBytes) {
	//explicitly create a json file, but soon or later imma remove this
	nlohmann::json json;
	json["Post"] = sizeToSendInBytes;
	// std::cout << json.dump();
	return json.dump();
}

const bool JsonFunction::getJsonRequest(
	const std::string& msg,
	JsonRequests& req
) {
	if (msg.empty()) {
		printf("the recieve msg is empty!\n");
		return false;
	}

	nlohmann::json json = nlohmann::json::parse(msg);
	if(json.contains("Deactivate")) {
		return false;
	}
	return false;
}

const int JsonFunction::getReqAndSize(
	const std::string& msg,
	HTTPReq& req
) {
	if (msg.empty()) {
		printf("the recieve msg is empty!\n");
		return -1;
	}
	nlohmann::json json = nlohmann::json::parse(msg);
	if (json.contains("Post") == false){
		printf("cannot handle different request types in this funciton\n");
		return -1;
	}
	req = HTTPReq::Post;
	return json.value("Post", 0);
}
