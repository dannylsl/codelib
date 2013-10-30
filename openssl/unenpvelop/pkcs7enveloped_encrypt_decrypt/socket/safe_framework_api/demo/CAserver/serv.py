# filename	: serv.py 
# author	: danny lee
# date		: 2013-07-10
# email		: dannylsl@hotmail.com
# brief		: [Server] file transform in socket

from socket import * 
import os
import sys 
import pexpect
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
	print 'fileInfo sent'
	
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

	#prefix = 'recv_'
	filename = prefix + recvFileName  #Add 'recv_' prefix
	fp = open(filename,'wb')

	BUFSIZE = 1024
	restsize = recvFileSize 

	while True:
		if restsize > BUFSIZE:
			filedata = connect.recv(BUFSIZE)
		else:
			filedata = connect.recv(restsize)
		if not filedata: 
			break;
		fp.write(filedata)
		restsize = restsize - len(filedata)			
		if restsize == 0: break
	fp.close()


##
# deal with certification application file
##
def deal(certReqName):

	print 'certification application name:'+certReqName

	if os.path.isfile('./usercert.pem'):
		print certReqName + " is exist, remove it"
		os.remove('./usercert.pem')

	os.system('exit')
	child = pexpect.spawn('openssl ca -in %s -out %s \n' % (certReqName,'./usercert.pem'))
	child.logfile = sys.stdout
	child.expect('Enter pass phrase for')
	child.send('123456\n')
	child.expect('y/n')
	child.send('y\n')
	child.expect('y/n')
	child.send('y\n')
	child.expect('Data Base Updated')
	print 'usercert created'

	os.system('openssl x509 -in usercert.pem -inform PEM -out usercert.der -outform DER')


########################################
# main
########################################
if __name__ == '__main__':
	s = socket(AF_INET,SOCK_STREAM)

	#host = socket.gethostname()
	#port = 6000

#	print host+":"+str(port)

	ADDR = ('192.168.1.103',6000)
#	ADDR = ('127.0.0.1',6000)

#	s.bind((host,port))
	s.bind(ADDR)

	s.listen(5) 
	
	print 'start...'

	while True:
		connect, addr = s.accept()
		INFOLEN = 64	
		fileInfo = connect.recv(INFOLEN)
		recvFileName = fileInfo.strip('#').split('$')[0]
		recvFileSize = int(fileInfo.strip('#').split('$')[1])
		print 'receive file:'+recvFileName +' filesize:'+str(recvFileSize)
		recvFile(connect,recvFileName,recvFileSize,'srecv_')
		print 'srecv_'+recvFileName + ' received successfully!'
	
		print 'Start dealing with certification request file'
		deal('srecv_'+recvFileName)		

		print 'start sending file b.txt' 
		sendFileInfo(connect,'./','usercert.der')
		sendFile(connect,'./','usercert.der')
	
		child = pexpect.spawn("sudo openssl ocsp -index ./demoCA/index.txt -CA ./demoCA/cacert.pem \
				-rsigner ./demoCA/cacert.pem -rkey ./demoCA/private/cakey.pem -port 9999")
		child.logfile = sys.stdout
		child.expect('Enter pass phrase for')
		child.send('123456\n')
		child.expect('Waiting for OCSP')

		connect.close()
	s.close()

