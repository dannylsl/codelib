#!/bin/python

# Python class Exception process
# 1. RETRUN NONE IN __new__ IF PARAMETER CHECK RETURN FALSE
# 2. RAISE EXCEPTION IN __init__ IF PARAMETER CHECK RETURN FALSE
# 3. RAISE EXCEPTION IN __new__ IF PARAMETER CHECK RETURN FALSE

import os
import time

class Foo(object):

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
        print "FOO __del__ called"


class Foo2(object) :
### raise Exception while failed to initialize instance
    def __init__(self, file) :
        print "Foo2 __init__ called"
        if os.path.exists(file) == False :
            raise ValueError("File not exist while Foo2")

    def __del__(self) :
        print "FOO2 __del__ called"



class Foo3(object) :
    def __new__(cls, file) :
        print "Foo3 __new__ called"
        if os.path.exists(file) == False :
            raise ValueError("File not exist while Foo3")
        print "Foo3 __new__ called END"

    def __init__(self, file) :
        print "Foo3 __init__ called"

    def __del__(self) :
        print "FOO3 __del__ called"


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

    print "11111" * 10
    try :
        foo2 = Foo2("aaa")
    except ValueError,e:
#       print_obj(foo2) # FAILED foo2 not exist
        print "ValueError:",e

    print "22222" * 10
    try :
        foo3 = Foo3("bbb")
    except ValueError,e:
        print "ValueError:",e

    print "Program End"
