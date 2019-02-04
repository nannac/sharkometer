import serial
from threading import Thread

class UART:

    def __init__(self, port, baud, timeout=3):
        self.port = port
        self.baud = baud
        self.timeout = timeout
        self.ser = serial.Serial(self.port, baudrate=self.baud, timeout=self.timeout)

    def receive(self, callback=None):
        self.ser.flushInput()
        while True:
            ser_bytes = self.ser.readline()
            decoded_bytes = str(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))
            if callback:
                callback(decoded_bytes)
            else:
                return decoded_bytes

    def command(self, command):
        if command in self.commands:
            self.transmit(command)
        else:
            pass

    def transmit(self, data):
        for d in data:
            self.ser.write(str(d))

    def connect(self):
        receiver = Thread(target = self.receive)
        receiver.start()

    def disconnect(self):
        pass

uart = UART("COM4", 9600, .1)
uart.connect()
