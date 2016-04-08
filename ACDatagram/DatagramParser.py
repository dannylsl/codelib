#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import sys
import ConfigParser

from Datagram import *

class DatagramParser:

    transType = ""
    gramPath = "./gramInfo/"
    datagramIn = None
    datagramOut = None

    def __init__(self, transtype) :
        self.transType = transtype
        iniPath = "%s%s.ini"%(self.gramPath, self.transType)

        if os.path.exists(iniPath) == False:
            print "Datagram[%s] Not Exist %s."%(transtype, iniPath)
            return None

        cf = ConfigParser.ConfigParser()
        cf.read(iniPath)

        sItems = cf.items('SEND')
        rItems = cf.items('RECV')

        self.datagramIn = Datagram(sItems)
        self.datagramOut = Datagram(rItems)


if __name__ == "__main__" :

    dg = DatagramParser(4023)
    if dg == None :
        print "Failed to Initialize"
        sys.exit()

    print dg.datagramIn.regions[0][1]
    print dg.datagramOut.regions[0][1]
    print dg.datagramIn.length
    print dg.datagramOut.length

    msg = "01934023      7054CT1234564000010000004942360010001676   0        A2T00000000000000201404176666666666666666    0               20                                                                    "

    ret = "014040230090847054CT1234564000010000004942360010001676   霞編001 000000000000A2T00000000000000201404176666666666666666    "

    dg.datagramIn.parser(msg)
    dg.datagramIn.printMsg()
    print 
    dg.datagramOut.parser(ret)
    dg.datagramOut.printMsg()
