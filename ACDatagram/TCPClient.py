#!/usr/bin/python
# -*- coding: utf-8 -*-

import socket
from log import log

class TCPClient :

    def __init__(self, host, port) :
        self.servHost = host
        self.servPort = port
        self.sock = socket.socket()
        self.sock.connect((host, port))

        log('C','TCPClient Initialized, Server[%s:%s] connected'%(host,port))

    def send(self, msg) :
        self.sock.send(msg)


    def recv(self, buffer_size = 1024) :
        return self.sock.recv(buffer_size)


    def __del__(self) :
        self.sock.close()
        log('C','TCPClient socket closed')


if __name__ == "__main__" :
    client = TCPClient('127.0.0.1', 12345)
    client.send("Hello World")

