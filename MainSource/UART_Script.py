#!/usr/bin/env python
from serial import Serial
import sys
from time import sleep

usart_message = "!"
print("Opening port...")
try:
    ser = Serial("/dev/ttyAMA0", 115200,timeout=1)    #Open port with baud rate
except serial.SerialException:
    print("Port could not be opened")
    exit()
print("Port opened!")
#                   #print received data

faultName  = sys.argv[1]
if faultName == "CONFIGCRK":message_identifier="1"
elif faultName == "CONFIGCAM":message_identifier="2"
elif faultName == "RESETCRK":message_identifier="3"
elif faultName == "RESETCAM":message_identifier="4"
elif faultName == "CRKRUNOUT":message_identifier="7"
elif faultName == "CAMPATERR":message_identifier="b"
elif faultName == "CAMDELAY":message_identifier="c"
elif faultName == "CRKTOOTHOFF":message_identifier="h"
elif faultName == "CRKGAPNOTDET":message_identifier="i"
elif faultName == "CRKPOSNENGSTST":message_identifier="l"
elif faultName == "CRKSEGADPERRLIM":message_identifier="j"
usart_message+=message_identifier

for i in range(2,len(sys.argv)):
    usart_message+= "/"+sys.argv[i]

usart_message+="%"
print(f'Data sent: {usart_message}')

ser.write(usart_message.encode())
sleep(0.03)   
databuffer = ser.in_waiting
if databuffer>0:
    received_data = ser.read(size=64)              #read serial port
    print (f'Data received: {received_data.decode()}')