#!/usr/bin/python

from prints import *
import os

class Procrank() :

    def __init__(self, filename) :
        print_msg('C', 'Class Procrank Object Initialized with file [%s]'%filename)
        self.filename = filename

        if os.path.exists(self.filename) == False :
            print_msg('E', "File [%s] is not exist"%self.filename)
            self.is_file_exist = False
        else :
            self.is_file_exist = True


    def get_vss(self, option) :
        print_msg('F', 'get_vss(%s) called'%option)
        if self.is_file_exist == False :
            vss = "NONE"
        else :
            procinfo = os.popen("cat %s | grep %s | awk '{print $2}'"%(self.filename, option))
            vss = procinfo.read().strip()
        return vss

    def get_rss(self, option) :
        print_msg('F', 'get_rss(%s) called'%option)
        if self.is_file_exist == False :
            rss = "NONE"
        else :
            procinfo = os.popen("cat %s | grep %s | awk '{print $3}'"%(self.filename, option))
            rss = procinfo.read().strip()
        return rss

    def get_pss(self, option) :
        print_msg('F', 'get_pss(%s) called'%option)
        if self.is_file_exist == False :
            pss = "NONE"
        else :
            procinfo = os.popen("cat %s | grep %s | awk '{print $4}'"%(self.filename, option))
            pss = procinfo.read().strip()
        return pss

    def get_uss(self, option) :
        print_msg('F', 'get_uss(%s) called'%option)
        if self.is_file_exist == False :
            uss = "NONE"
        else :
            procinfo = os.popen("cat %s | grep %s | awk '{print $5}'"%(self.filename, option))
            uss = procinfo.read().strip()
        return uss

    def get_data(self, option) :
        procdata = {
            "vss" : self.get_vss(option),
            "rss" : self.get_rss(option),
            "pss" : self.get_pss(option),
            "uss" : self.get_uss(option)
        };
        print procdata
        return procdata


if __name__ == "__main__" :
    procrank = Procrank("4test/procrank_video_playback_720p_30fps_VP9_power_withoutsocwatch_NONE_pre.txt")
    print procrank.get_vss('surfaceflinger')
    print procrank.get_rss('surfaceflinger')
    print procrank.get_pss('surfaceflinger')
    print procrank.get_uss('surfaceflinger')
    print procrank.get_vss('mediaserver')
    procrank.get_data('surfaceflinger')
    procrank.get_data('mediaserver')

