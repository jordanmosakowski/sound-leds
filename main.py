import sounddevice as sd
import numpy as np
import serial
import time
import math

# print(sd.query_devices())
ser = serial.Serial('COM3', 9600)
print("Initializing...")
time.sleep(5)
print("Connected to "+ser.name)

def print_sound(indata, outdata, frames, time, status):
    volume_norm = math.pow(np.linalg.norm(indata), 1.75) * 7
    if(volume_norm>255):
        volume_norm = 255.0
    data = str(int(volume_norm)) + "\n"
    ser.write(data.encode())
print("Running")
with sd.Stream(callback=print_sound):
    sd.sleep(1000000000)
