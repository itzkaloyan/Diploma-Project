from adafruit_motorkit import MotorKit
import time
import zmq
import sys
import json

kit = MotorKit()

def move(motor, val):
    if callable(motor.throttle):
        motor.throttle(val)
    else:
        motor.throttle = val

def SetMotor(arg):
    print(kit, kit.motor1, kit.motor1.throttle)
    move(kit.motor1, arg[0])
    move(kit.motor2, arg[1])
    print(f"SetMotor {arg}")

def Stop(arg):
    move(kit.motor1, 0.0)
    move(kit.motor2, 0.0)
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
        print(key)
        val = message[key]
        print(val)
        if key == None or key == "Deactivate":
            break
        func = kvp[key]
        print(func, kvp)
        func(val)
    socket.close()

if __name__ == "__main__":
    main()
