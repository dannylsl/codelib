# filename	: client.py 
# author	: danny lee
# date		: 2013-07-10
# email		: dannylsl@hotmail.com
# brief		: [Client] file transform in socket

import socket
import os
import os.path
from os.path import join,getsize

##
# pre-deal with fileInfo 
##
def infoDeal(fileInfo): 
	fill = '#'   
	infolen = len(fileInfo)				
	INFOLEN	= 64

	if infolen < INFOLEN:
		fileInfo += fill * (INFOLEN-infolen)

	return fileInfo

##
#  send fileInfo header before file transfrom
##
def sendFileInfo(sockConn,directory,filename):
	filesize = os.path.getsize(directory+filename)	
	fileInfo = '#'+filename+'$'+str(filesize)	
	print 'fileInfo:',fileInfo
	fileInfo = infoDeal(fileInfo)
	print 'fileInfo Len:',str(len(fileInfo))
	sockConn.send(fileInfo)

##
# send file
##
def sendFile(sockConn,directory,filename):
	print 'send file'+directory+filename 
	filesize = os.path.getsize(directory+filename)
	
	fp = open(filename,'rb') 
	while True:
		filedata = fp.read(filesize)
		if not filedata:
			break
		sockConn.send(filedata)
	fp.close()
	
##
# receive file
##
def recvFile(sockConn,recvFileName,recvFileSize,prefix):

#	prefix = 'recv_'
	filename = prefix + recvFileName  #Add 'recv_' prefix
	fp = open(filename,'wb')

	BUFSIZE = 1024
	restsize = recvFileSize 

	while True:
		if restsize > BUFSIZE:
			filedata = sockConn.recv(BUFSIZE)
		else:
			filedata = sockConn.recv(restsize)
		if not filedata: 
			break;
		fp.write(filedata)
		print 'restsize='+str(restsize)
		restsize = restsize - len(filedata)			
		if restsize == 0: break
	fp.close()

if __name__ == '__main__':
	#s = socket.socket()
	s = socket(AF_INET,SOCK_STREAM)

	#host = socket.gethostname()
	#port = 6000

	ADDR = ('127.0.0.1',6000)

	#s.connect((host,port))
	s.connect(ADDR)

	INFOLEN = 64

	filename = 'a.txt'
	sendFileInfo(s,'./',filename)	#sendFileInfo
	sendFile(s,'./',filename)		#send file 

############ RECEIVE FILE ###############
	fileInfo =  s.recv(INFOLEN)
	fileInfoArr = fileInfo.strip('#').split('$')
	print fileInfoArr[0] + " fileSize:" + fileInfoArr[1]
			
	recvFileName = fileInfoArr[0]
	recvFileSize = int(fileInfoArr[1])

	recvFile(s,recvFileName,recvFileSize,'crecv_')
	print 'crecv_'+recvFileName+' received successfully!'		
	s.close()


