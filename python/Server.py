import zmq
import time
import sys
import json

def SetMotor(arg):
    print(f"SetMotor {arg}")
def Left(arg):
    print(f"Left {arg}")
def Right(arg):
    print(f"Right {arg}")
def Foreward(arg):
    print(f"Foreward {arg}")
def Backward(arg):
    print(f"Backward {arg}")
def Stop(arg):
    print(f"Stop {arg}")

kvp = {
    "SetMotors":SetMotor,
	"Left":Left,
	"Right":Right,
	"Foreward":Foreward,
	"Backward":Backward,
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
