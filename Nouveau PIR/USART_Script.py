import serial
import sys
from time import sleep

print(sys.argv)
usart_message = "!"
#ser = serial.Serial("/dev/ttyS0", 9600)    #Open port with baud rate
#received_data = ser.read()              #read serial port
sleep(0.03)
#data_left = ser.inWaiting()             #check for remaining byte
#received_data += ser.read(data_left)
#print (received_data)                   #print received data

testName  = sys.argv[1]
message_identifier = "0"
if testName == "CONFIGCRK":message_identifier="1"
elif testName == "CONFIGCAM":message_identifier="2"
elif testName == "RESETCRK":message_identifier="3"
elif testName == "RESETCAM":message_identifier="4"
elif testName == "CRKRUNOUT":message_identifier="7"
elif testName == "CAMPATERR":message_identifier="b"
elif testName == "CAMDELAY":message_identifier="c"
elif testName == "CRKTOOTHOFF":message_identifier="h"
elif testName == "CRKGAPNOTDET":message_identifier="i"
elif testName == "CRKPOSNENGSTST":message_identifier="l"
elif testName == "CRKSEGADPERRLIM":message_identifier="j"
usart_message+=message_identifier

for i in range(2,len(sys.argv)):
    usart_message+= "/"+sys.argv[i]

usart_message+="%"
print(usart_message)

#ser.write(message_identifier)   
