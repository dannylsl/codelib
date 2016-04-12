#!/usr/bin/python
# -*- coding: utf-8 -*-

import time

from TCPClient import TCPClient
from TCPServ import TCPServThread
from DatagramParser import DatagramParser
from log import log

class DatagramTransfer :

    def __init__(self, localPort, servHost, servPort) :
        self.serv = None
        self.client = None
        self.startServ(localPort)
        self.startClient(servHost, servPort)


    def startServ(self, port = 6000) :
        self.serv = TCPServThread('0.0.0.0', port)
        self.serv.setDaemon(True)
        self.serv.start()
        pass


    def startClient(self, host, port) :
        self.client = TCPClient(host, port)
        pass


    def sendMsg(self,msg) :
        self.client.send(msg)
        log('D', "[%s]"%msg)
        pass


    def sendMsgWaitForReply(self, msg) :
        self.client.send(msg)
        while self.serv.recvBuffer == "" :
            pass
        return self.serv.flashRecvBuffer()


    def recvMsg(self) :
        if self.serv.recvBuffer != "" :
            return self.serv.flashRecvBuffer()
        else :
            return ""


    # 设置报文格式并结构化报文
    def setDatagram(self, transtype, datagramIn) :
        self.dgParser = DatagramParser(transtype)
        self.dgParser.datagramIn.parser(datagramIn)


    # 发送报文,并等待获取结果报文,并格式化
    def sendDatagramAndGetReply(self) :
        self.client.send(self.dgParser.datagramIn.msg)
        while self.serv.recvBuffer == "" :
            pass
        reply = self.serv.flashRecvBuffer()
        self.dgParser.datagramOut.parser(reply)


if __name__=="__main__" :
    dgTransfer = DatagramTransfer(6000, '127.0.0.1', 12345)
    for i in range(5,10) :
        #print dgTransfer.sendMsg("Hello World %d"%i)
        #print dgTransfer.sendMsgWaitForReply("Hello World %d"%i)
        msg = "01934023      7054CT1234564000010000004942360010001676   0        A2T00000000000000201404176666666666666666    0               20                                                                    "
        dgTransfer.setDatagram(4023, msg)
        dgTransfer.sendDatagramAndGetReply()
        dgTransfer.dgParser.datagramOut.printMsg()
        time.sleep(1)


#    serv = TCPServThread('0.0.0.0', 6000)
#    serv.setDaemon(True)
#    serv.start()
#
#    client = TCPClient('127.0.0.1', 12345)
#    for i in range(1,5) :
#        client.send("Hello World %d"%i)
#        log('M', 'Hello world %d'%i)
#        time.sleep(1)

