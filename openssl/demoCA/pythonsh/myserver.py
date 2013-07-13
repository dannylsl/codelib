# fileName	: myserver.py
# author	: danny lee
# email		: dannylsl@hotmail.com
# date		: 2013-07-10
# brief		: CA Server

from socket import*
import struct
import sys
import pexpect
import os
from os import system
from os.path import join,getsize

# ##############################################
# distribute certification
# ##############################################
def distCert(sock,certName)
	BUFSIZE = 1024
	
