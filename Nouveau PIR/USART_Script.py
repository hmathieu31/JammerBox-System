import serial
import sys
from time import sleep

print(sys.argv[1],sys.argv[2],sys.argv[3])

testName  = sys.argv[1]
testParameter = sys.argv[2]
data = sys.argv[3]

message_identifier = 0

ser = serial.Serial("/dev/ttyS0", 9600)    #Open port with baud rate
received_data = ser.read()              #read serial port
sleep(0.03)
data_left = ser.inWaiting()             #check for remaining byte
received_data += ser.read(data_left)
print (received_data)                   #print received data

if testName == "CONFIGCRK":message_identifier="1"
elif testName == "CONFIGCAM":message_identifier="2"
elif testName == "RESETCRKCONFIG":message_identifier="3"
elif testName == "RESETCAMCONFIG":message_identifier="4"
elif testName == "CRKRUNOUT":message_identifier="7"
elif testName == "CAMPATERR":message_identifier="b"
elif testName == "CAMDELAY":message_identifier="c"
elif testName == "CRKTOOTHOFF":message_identifier="h"
elif testName == "CRKGAPNOTDET":message_identifier="i"
elif testName == "CRKPOSNENGSTST":message_identifier="l"
elif testName == "CRKSEGADPERRLIM":message_identifier="j"



ser.write(message_identifier)   
