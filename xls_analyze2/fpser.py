#encoding: UTF-8
import re
import os
import traceback
from prints import *

class FPS() :
    filehandle  = None
    filename    = None
    regex       = ""
    fps         = 0.0

    def __init__(self, filename, regex) :
        print_msg('C', 'Class FPS Object Initialized with file [%s]'%filename)
        self.filename   = filename

        if os.path.exists(filename) == False :
            self.is_file_exist = False
            print_msg('E', 'File Not Exist [%s]'%filename)
        else :
            self.is_file_exist = True

        self.regex      = regex
        self.getfps()


    def getfps(self) :
        pattern = re.compile(r'%s'%self.regex)

        if self.is_file_exist == True :
            self.filehandle = open(self.filename, 'r')
            line = self.filehandle.readline()
            while line :
                match = pattern.search(line)

                if match :
                    match_fps = match.group()
                    fps_arr = match_fps.split('=')
                    if float(fps_arr[1]) < 1 :
                        self.fps = 0.0
                    else :
                        self.fps=float(fps_arr[1])

                line = self.filehandle.readline()

            self.filehandle.close()
        else :
            self.fps = "NONE"




#fps = FPS('fps_video_playback_1080p_fps_stagefright', 'render_FPS=[0-9]*\.[0-9]*')
#fps.getfps()
#print fps.fps
