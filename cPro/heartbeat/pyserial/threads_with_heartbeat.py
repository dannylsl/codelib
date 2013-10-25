import time 
import thread
import threading
import serial
import ConfigParser


def heartbeat_mutex_lock(mutex) :
	print "heartbeat_mutex_lock"
	if mutex.acquire():	
		print "heartbeat_mutex_lock OK" 	

def heartbeat_mutex_unlock(mutex) :
	print "heartbeat_mutex_unlock"
	mutex.release()

def serial_heartbeat(serial,  config, mutex) :
	print "SERIAL HEARTBEAT"
	
	while 1:
		serial.write('ls\r\n')		
		out = ''
		time.sleep(3)
		
		while ser.inWaiting() > 0:
			out += ser.read(1)
#print out

		if out != '':
			print "device SET 1" 
			heartbeat_mutex_lock(mutex)
			config.set('device', 'state','1')
			heartbeat_mutex_unlock(mutex)
		else :
			print "device SET 0" 
			heartbeat_mutex_lock(mutex)
			config.set('device', 'state','0')
			heartbeat_mutex_unlock(mutex)
			exit()

def check_device_state(config, mutex):
	heartbeat_mutex_lock(mutex)
	state = config.get('device', 'state')	
	heartbeat_mutex_unlock(mutex)
	if state == "1" :
		print "device alive" 
	elif state == "0" :
		print "device crashed"
					

if __name__ == '__main__' :

	cf = ConfigParser.ConfigParser()
	cf.read("hb.conf")	

	s_port = cf.get('serial', 'port')	
	s_baudrate = cf.get('serial', 'baudrate')

	ser = serial.Serial(
		port = s_port, 
		baudrate = s_baudrate, 
		parity=serial.PARITY_ODD, 
		stopbits=serial.STOPBITS_TWO, 
		bytesize=serial.SEVENBITS
	)

	ser.open()	
	ser.isOpen()

	cf.set('device', 'state','1')

	mutex = threading.Lock()

	thread.start_new_thread( serial_heartbeat,  (ser, cf, mutex))
#check_device_state(cf,  mutex)


	while 1:
		time.sleep(5)
		print "main"	
