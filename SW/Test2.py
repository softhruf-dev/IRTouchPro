import serial, time, threading, signal

line = []

exitThread = False

def handler(signum, frame):
    exitThread = True

def parsing_data(data):
    tmp = ''.join(data)
    print(tmp)

def readThread(ser):
    global line
    global exitThread

    while not exitThread:
        for c in ser.read():
            line.append(chr(c))
            if c == 10:
                parsing_data(line)
                if line[0]=='1' and line[1]=='0':
                    ser.write(b'hehehe')
                del line[:]
            elif chr(c) == 'A':
                print(line[:-1])
                del line[:]

    ser.close()

if __name__ == "__main__":
    signal.signal(signal.SIGINT, handler)
    ser = serial.Serial(port='COM3', baudrate=9600, parity='N', stopbits=1, timeout=0)
    thread = threading.Thread(target=readThread, args=(ser,))
    thread.start()
