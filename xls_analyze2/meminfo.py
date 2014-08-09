#!/usr/bin/python

import re
import os
from prints import *

class MemoryInfo() :

    def __init__(self, filename) :
        print_msg('C', 'MemoryInfo Initialized with file [%s]'%filename)
        self.filename = filename

        if os.path.exists(self.filename) == False :
            print_msg('E', "File [%s] is not exist"%self.filename)
            self.is_file_exist = False
        else :
            self.is_file_exist = True

        self.get_memTotal()
        self.get_memFree()
        self.get_memCached()

    def get_memTotal(self) :
        print_msg('F', 'get_memTotal called')
        if self.is_file_exist == False :
            self.memTotal = "NONE"
        else :
            meminfo = os.popen("cat %s | grep MemTotal | sed 's/MemTotal: *//'"%self.filename)
            self.memTotal = meminfo.read().strip()
#        print "MemTotal=",self.memTotal

    def get_memFree(self) :
        print_msg('F', 'get_memFree called')
        if self.is_file_exist == False :
            self.memFree = "NONE"
        else :
            meminfo = os.popen("cat %s | grep MemFree | sed 's/MemFree: *//'"%self.filename)
            self.memFree = meminfo.read().strip()
#        print self.memFree

    def get_memCached(self) :
        print_msg('F', 'get_memcached called')
        if self.is_file_exist == False :
            self.memCached = "NONE"
        else :
            meminfo = os.popen("cat %s | grep ^Cached | sed 's/Cached: *//'"%self.filename)
            self.memCached = meminfo.read().strip()
#        print self.memCached


if __name__ == "__main__" :
    meminfo = MemoryInfo("4test/memoryinfo_video_playback_720p_30fps_VP9_power_withoutsocwatch_NONE_next.txt")
