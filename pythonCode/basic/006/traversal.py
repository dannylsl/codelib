#!/usr/bin/python
# -*- coding: utf-8 -*-

import os

def walk_test(rootDir) :
    list_dirs = os.walk(rootDir)
    for root, dirs, files in list_dirs :
        for d in dirs :
            print os.path.join(rootDir, d)
        for f in files :
            print os.path.join(rootDir, f)

def listdir_test(rootDir) :
    for lists in os.listdir(rootDir) :
        path = os.path.join(rootDir, lists)
        print path
        if os.path.isdir(path) :
            listdir_test(path)

if __name__ == '__main__' :
    rootDir = '/dev/'
    walk_test(rootDir)
    print "+++" * 10
    listdir_test(rootDir)

    print "+++" * 10
    print "+++" * 10
    for lists in os.listdir(rootDir) :
        print lists
        path = os.path.join(rootDir, lists)
        print path


