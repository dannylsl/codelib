#!/bin/python
import os

class Foo(object):
#    file = ""

###   RETURN NONE when Failed to create class Instance
    def __new__(cls, file = "/dev/ttyUSB0") :
        print "__new__ called file=\'%s\'"%file

        if os.path.exists(file) == False :
#            cls.file = file
            print "File not exist"
            return None
        else :
            print "Object created"
            #return cls
            return super(Foo, cls).__new__(cls, file = "/dev/ttyUSB0")

    def __init__(self, file="/dev/ttyUSB0") :
        self.file = file
        print "*** __init__ called ***"
        print "file=%s"%self.file
        print "**" * 10

    def __del__(self) :
        print ">>>>>>>>>> __del__ called"


class Foo2(object) :
### raise Exception while failed to initialize instance
    def __init__(self, file) :
        if os.path.exists(file) == False :
            raise RuntimeError
        # TO BE DONE




def print_obj(obj) :
    if obj == None :
        print "foo = None"
    else :
        print obj
        #print repr(obj)

if __name__ == '__main__' :

    foo = Foo("ttyUSB01111111")
    print_obj(foo)

    print "==" * 10
    foo1 = Foo("example")
    print_obj(foo1)
