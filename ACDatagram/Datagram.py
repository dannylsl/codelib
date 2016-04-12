#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import re

# list 索引位置
ID      = 0
CHINESE = 1
ENGLISH = 2
TYPE    = 3
LENGTH  = 4
DECIMAL = 5
VALUE   = 6

class Datagram:

    def __init__(self, items) :
        self.length = 0         # 报文长度
        self.regions = []       # 结构化报文
        self.regions_cnt = 0    # 报文域数目
        self.msg = ""           # 存储字符串格式报文

        region = list()
        for item in items :
            region.append(item[0])
            st_arr = item[1].split()
            region.append(st_arr[0].strip())
            region.append(st_arr[1].strip())
            region.append(st_arr[2].strip())

            if ',' in st_arr[3] :
                region.append(int(st_arr[3].split(',')[0]))
                region.append(int(st_arr[3].split(',')[1]))
            else :
                region.append(int(st_arr[3].split(',')[0]))
                region.append(0)

            self.regions.append(region)
            region = []

        self.length = self.getLength();
        self.regions_cnt = len(self.regions)


    # 获取报文region长度
    def getLength(self) :
        length = 0
        for region in self.regions :
            length = length + int(region[4])
        return length


    # 对报文进行解析，对应到region结构,并格式化
    def parser(self, msg) :
        global LENGTH

        #报文前四个字符表示报文长度
        if int(msg[0:4]) != self.length or int(msg[0:4]) != len(msg) - 4 :
            print "Message length[%d] invalid"%len(msg)
            sys.exit()

        start_index = 0
        end_index = 0

        for i in range(0, self.regions_cnt) :
            if i == 0 :
                start_index = 4
            else :
                start_index = end_index
            end_index = start_index + int(self.regions[i][LENGTH])

            #print start_index,end_index
            self.regions[i].append(msg[start_index:end_index])

        self.msg = msg


    # 格式化打印报文
    def printMsg(self) :
        for region in self.regions :
            print "[%3s] %-s %s"%(region[ID], region[ENGLISH].ljust(10), region[VALUE])


    def __del__(self) :
        del self.length
        del self.regions[:]
