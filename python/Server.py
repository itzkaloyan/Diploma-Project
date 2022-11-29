# from adafruit_motorkit import MotorKit
# import time
import zmq
import sys
import json

# kit = MotorKit()

def SetMotor(arg):
    # kit.motor1.throttle(arg[0])
    # kit.motor2.throttle(arg[1])
    print(f"SetMotor {arg}")
def Stop(arg):
    # kit.motor1.throttle(0.0)
    # kit.motor2.throttle(0.0)
    print(f"Stop {arg}")

kvp = {
    "SetMotors":SetMotor,
	"Stop":Stop
}

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://127.0.0.1:5555")

def listenForCommand():
    messageAfterSocketRcv = socket.recv().decode()
    message = json.loads(messageAfterSocketRcv)
    print(f"Received request: {message}")
    socket.send(b"recieved function")
    res = True
    if("Deactivate" in message.keys()):
        res = False
    return (message, res)

def main():
    while(True):
        message, res = listenForCommand()
        keysList = list(message.keys())
        key = keysList[0]
        val = message[key]
        if key == None or key == "Deactivate":
            break
        kvp[key](val)
    socket.close()

if __name__ == "__main__":
    main()
