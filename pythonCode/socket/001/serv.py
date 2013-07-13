# filename	: serv.py 
# author	: danny lee
# date		: 2013-07-10
# email		: dannylsl@hotmail.com
# brief		: [Server] basic socket communication

import socket

s = socket.socket()

host = socket.gethostname()
port = 6000
s.bind((host,port))

s.listen(5)
while True:
	connect, addr = s.accept()
	print 'Got connection from', addr
	print "receive string from client :",connect.recv(1024)
	connect.send('Thank you for connecting')
	connect.close()
