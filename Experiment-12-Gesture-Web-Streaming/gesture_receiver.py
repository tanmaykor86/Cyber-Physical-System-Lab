import serial

ser = serial.Serial("COM11", 9600)

print("Waiting for gestures...")

while True:
    if ser.in_waiting:
        gesture = ser.readline().decode().strip()

        print(gesture)

        with open("gesture.txt", "w") as f:
            f.write(gesture)