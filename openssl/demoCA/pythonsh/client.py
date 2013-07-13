# -*- coding: cp936 -*-
from socket import *
import os
import struct
from os.path import join,getsize

###############################################################################
#send file to socket
###############################################################################
def sendFile(sendSock):
	#filename = 'pkcs10.pem'
	filename = 'certreq.pem'
#	FILEINFO_SIZE=struct.calcsize('128s32sI8s')
	 
	#fhead=struct.pack('128s11I',filename,0,0,0,0,0,0,0,0,os.stat(filename).st_size,0,0)
	#sendSock.send(fhead)
	 
	fp = open(filename,'rb')
	while 1:
	    filedata = fp.read(BUFSIZE)
	    if not filedata: break
	    sendSock.send(filedata)
	fp.close()

###############################################################################
#recv file to socket
###############################################################################
def recvFile(conn):

	#fhead = conn.recv(FILEINFO_SIZE)
	#filename,temp1,filesize,temp2=struct.unpack('128s32sI8s',fhead)
	#print filename,temp1,filesize,temp2
	#print filename,len(filename),type(filename)
	#print filesize
	 
#	filename = 'new_'+ "pkcs10.pem"
	filename = 'recv_'+ 'usrcert.pem'
	fp = open(filename,'wb')
#	restsize = 1054
	restsize = 448
	restsize = os.path.getsize("../../usercert.der")
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


if __name__ == '__main__':
	#ADDR = ('192.168.213.204',10100)
	ADDR = ('127.0.0.1',10100)
	FILEINFO_SIZE=struct.calcsize('128s32sI8s')
	BUFSIZE = 1024

	sendSock = socket(AF_INET,SOCK_STREAM)
	sendSock.connect(ADDR)
	 
	sendFile(sendSock)
	
	recvFile(sendSock)
 
	sendSock.close()


