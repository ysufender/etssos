import serial
import threading
import sys

if len(sys.argv) != 3:
    print(f"Usage: {sys.argv[0]} <port> <baud>")
    sys.exit(1)

s = serial.Serial(sys.argv[1], int(sys.argv[2]))

def read_loop():
    while True:
        line = s.read(s.in_waiting or 1)
        print(line.decode('utf-8', errors='ignore'), end='', flush=True)

t = threading.Thread(target=read_loop, daemon=True)
t.start()

while True:
    try:
        line = input()
        s.write((line + '\n').encode('utf-8'))
    except EOFError:
        break
