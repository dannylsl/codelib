#encoding: UTF-8
import re
import os
import traceback

class FPS() :
    filehandle  = None
    filename    = None
    regex       = ""
    fps         = 0.0

    def __init__(self, filename, regex) :
#        print "__init__ called, filename=%s"%filename
        self.filename   = filename
        self.regex      = regex
        self.getfps()


    def getfps(self) :
        pattern = re.compile(r'%s'%self.regex)

        try :
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

        except Exception:
            exstr = traceback.format_exc()
            print "Error: %s"%exstr
            print "Failed to init the FPS Object"


    def __del__(self) :
        pass
#        print "__del__ called"


#fps = FPS('fps_video_playback_1080p_fps_stagefright', 'render_FPS=[0-9]*\.[0-9]*')
#fps.getfps()
#print fps.fps
