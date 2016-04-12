#!/usr/bin/python
# -*- coding: utf-8 -*-

import threading
import socket
import time
from log import log

class TCPServThread(threading.Thread) :

    def __init__(self, host, port) :
        threading.Thread.__init__(self)
        self.host = host
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind((host, port))
        self.sock.listen(5)
        self.recvBuffer = ""

        log('C', "TCPServThread Initialized %s:%s"%(host,port))


    def flashRecvBuffer(self) :
        tmpBuffer = self.recvBuffer
        self.recvBuffer = ""
        return tmpBuffer


    def run(self) :
        #连接Sever, 只连接一次
        self.connect, self.addr = self.sock.accept()
        log('M',self.addr)

        while True:
            self.recvBuffer = self.connect.recv(1024)
            if self.recvBuffer != "" :
                log('M', '[ServThread LEN] %d'%len(self.recvBuffer))
                log('M', '[SeverThread RECV] [%s]'%self.recvBuffer)


    def __del__(self) :
        self.connect.close()
        self.sock.close()
        log('C','TCPServThread socket closed')


if __name__ == "__main__":

    serv = TCPServThread('0.0.0.0', 6000)
    serv.setDaemon(True)
    serv.start()
    while True:
        pass
