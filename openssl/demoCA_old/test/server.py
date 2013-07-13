# -*- coding: cp936 -*-
from socket import *
import struct
import sys
import pexpect
import os
from os import system

###############################################################################
#send file to socket
###############################################################################
def sendFile(sendSock):
	BUFSIZE = 1024
	filename = 'usercert.der'
#	FILEINFO_SIZE=struct.calcsize('128s32sI8s')
#	 
#	fhead=struct.pack('128s11I',filename,0,0,0,0,0,0,0,0,os.stat(filename).st_size,0,0)

	#sendSock.send(fhead)
	 
	fp = open(filename,'rb')
	while 1:
	    filedata = fp.read(BUFSIZE)
	    if not filedata: break
	    sendSock.send(filedata)
	fp.close()
###############################################################################

###############################################################################
#recv file to socket
###############################################################################
def recvFile(conn):

#	fhead = conn.recv(FILEINFO_SIZE)
#	filename,temp1,filesize,temp2=struct.unpack('128s32sI8s',fhead)
#	#print filename,temp1,filesize,temp2
#	print filename,len(filename),type(filename)
#	print filesize
	filename = "userreq.pem"
	restsize = 1054
	 
	filename = 'new_'+filename.strip('\00') #...
	fp = open(filename,'wb')
	while 1:
	    if restsize > BUFSIZE:
		filedata = conn.recv(BUFSIZE)
	    else:
		filedata = conn.recv(restsize)
	    if not filedata: break
	    fp.write(filedata)
	    restsize = restsize-len(filedata)
	    if restsize == 0: break
	fp.close()
	return filename
###############################################################################



###############################################################################
#deal with the userreq.pem
###############################################################################
def deal(filename):
	print "the filename is " + filename

	if os.path.isfile("./usercert.pem"):
		print "yes"
		os.remove("./usercert.pem")

	os,system('exit')
	#os.system('openssl ca -in %s -out %s' % ( filename, "./usercert.pem"))
	child = pexpect.spawn('openssl ca -in %s -out %s \n' % (filename, "./usercert.pem"))
	#child = pexpect.spawn('openssl ca -in %s -out %s' % ( filename, "./usercert.pem"))
	child.logfile = sys.stdout
	child.expect('Enter pass phrase for')
	child.send('123456\n')
	child.expect('y/n')
	child.send('y\n')
	child.expect('y/n')
	child.send('y\n')
	child.expect('Data Base Updated')
	print "DONE"



	os.system('openssl x509 -in usercert.pem -inform PEM -out usercert.der -outform DER')
###############################################################################




###############################################################################
#main function
###############################################################################

if __name__ == '__main__':
#	ADDR = ('192.168.213.204',10100)
	ADDR = ('127.0.0.1',10010)
	BUFSIZE = 1024
	FILEINFO_SIZE=struct.calcsize('128s32sI8s')
	 
	recvSock = socket(AF_INET,SOCK_STREAM)
	recvSock.bind(ADDR)
	recvSock.listen(True)
	
	 
	while True:

		print "wait..."
		conn,addr = recvSock.accept()
		print "send from ",addr


		if 'child' in locals().keys():
			child.close()
		 
		filename = recvFile(conn)
		deal(filename)
		sendFile(conn)

		child = pexpect.spawn("sudo openssl ocsp -index ../index.txt -CA ../cacert.pem -rsigner ../cacert.pem -rkey ../private/cakey.pem -port 9999")
		#child = pexpect.spawn('openssl ca -in %s -out %s' % ( filename, "./usercert.pem"))
		child.logfile = sys.stdout
		child.expect('Enter pass phrase for')
		child.send('123456\n')
		child.expect('Waiting for OCSP')
	
		conn.close()

	recvSock.close()
	 
###############################################################################
