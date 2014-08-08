#!/usr/bin/python

import re
import os
from prints import *

class mediaFPS() :

    def __init__(self, filename) :
        print "mediafps __init__ called"
        self.frate = 0
        self.filename = filename

        if os.path.exists(filename) == False :
            self.is_file_exist = False
            print_msg('E', 'File Not Exist [%s]'%filename)
        else :
            self.is_file_exist = True

        self.regex = "Frame rate.*:.*fps"
        self.get_mp4_fps()

    def get_mp4_fps(self) :
        pattern = re.compile(r'%s'%self.regex)

        if self.is_file_exist == True :
            self.filehandle = open(self.filename, 'r')
            line = self.filehandle.readline()
            while line :
                match = pattern.search(line)

                if match :
                    match_fps = match.group()
                    fps_arr = match_fps.split(':')
                    self.frate = re.sub('fps$', '', fps_arr[1].strip())
                line = self.filehandle.readline()

            self.filehandle.close()

        else :
            self.frate = "NONE"


#mfps = mediafps("mediainfo_mp4_record")
#mfps.get_mp4_fps()
