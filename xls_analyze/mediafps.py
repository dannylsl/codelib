#!/usr/bin/python

import re

class mediaFPS() :

    def __init__(self, filename) :
        print "mediafps __init__ called"
        self.frate = 0
        self.filename = filename
        self.regex = "Frame rate.*:.*fps"
        self.get_mp4_fps()

    def get_mp4_fps(self) :
        pattern = re.compile(r'%s'%self.regex)

        try :
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

        except Exception:
#            exstr = traceback.format_exc()
#            print "Error: %s"%exstr
            print "Failed to init the FPS Object"
            self.frate = 0

    def get_frate(self) :
        return self.frate


#mfps = mediafps("mediainfo_mp4_record")
#mfps.get_mp4_fps()
