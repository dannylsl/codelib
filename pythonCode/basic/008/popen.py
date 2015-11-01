import os

class Object() :

    def __init__(self) :
        print "Object Initialize"
        self.cmd_res = "000"

    def exe_cmd(self) :
        print "exe_cmd() called"
        res = os.popen("ls")
        self.cmd_res = res.read()
        print "cmd_res=",self.cmd_res

        res2 = os.popen("ls")
        tmp  = res2.read()
        print "tmp=",tmp


if __name__ == "__main__" :
    obj = Object()
    obj.exe_cmd()

