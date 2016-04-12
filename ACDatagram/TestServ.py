#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
from TCPServ import TCPServThread
from TCPClient import TCPClient
from log import log


if __name__=="__main__" :

    serv = TCPServThread('0.0.0.0', 12345)
    serv.setDaemon(True)
    serv.start()

    while serv.recvBuffer == "" :
        pass

    client = TCPClient('127.0.0.1', 6000)
    #recvMsg = serv.flashRecvBuffer()

    while True :
        if serv.recvBuffer != "" :
            recvMsg = serv.flashRecvBuffer()
            log('M','[RECV] %s'%recvMsg)
            ret = "014040230090847054CT1234564000010000004942360010001676   霞編001                       000000000000A2T00000000000000201404176666666666666666    "
            log('D', '[SEND] LEN %d'%len(ret))
            log('D','[SEND] [%s]'%ret)
            client.send(ret)
