import time
import serial
import threading
import ConfigParser

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
		port='/dev/ttyUSB2',
		baudrate=115200,
		parity=serial.PARITY_ODD,
		stopbits=serial.STOPBITS_TWO,
		bytesize=serial.SEVENBITS
)

ser.open()
ser.isOpen()

input=1
while 1 :
	# send the character to the device
	# (note that I happend a \r\n carriage return and line feed to the characters - this is requested by my device)
	ser.write('ls\r\n')
	out = ''
	# let's wait one second before reading output (let's give device time to answer)
	time.sleep(3)
	while ser.inWaiting() > 0:
		out += ser.read(1)

	print out
	if out != '':
		print 'device alive'
	else :
		print 'device crashed'
		exit()

