# filename	: client.py 
# author	: danny lee
# date		: 2013-07-10
# email		: dannylsl@hotmail.com
# brief		: [Client] basic socket communication

import socket

s = socket.socket()

host = socket.gethostname()
port = 6000

s.connect((host,port))
string = "hello world" 
print 'send string from client to server.',string
s.send(string)
print s.recv(1024)
