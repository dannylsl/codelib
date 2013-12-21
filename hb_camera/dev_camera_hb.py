#!/usr/usr/bin/python

import pygame
import pygame.camera
from pygame.locals import *

import os
import time

## import for image_similarity
import Image
from numpy import average, linalg, dot
import sys


class cameraHB() :

    def __init__(self, dev = "/dev/video0", size_w = 640, size_h = 480) :
        print "cameraHB __init__ called"
        self.size_width = size_w
        self.size_height= size_h
        self.dev        = dev
        self.ui_state  = True

        pygame.init()
        pygame.camera.init()
        self.cam = pygame.camera.Camera(self.dev, (self.size_width, self.size_height))

        ## start camera here ?
        self.cam.start()

    def __del__(self) :
        print "camera __del__ called"
        ## stop camera here ?
        self.cam.stop()

    def get_single_image(self, img_name) :
        print "Get a single image:", img_name, "\n"
        image = self.cam.get_image()
        pygame.image.save(image,img_name)
        print "image saved"

    def get_single_image_flush_buffer(self, img_name) :
        print "Get a single image flush buffer:", img_name, "\n"
        image = self.cam.get_image()
        image = self.cam.get_image()
        image = self.cam.get_image()
        pygame.image.save(image,img_name)
        print "image saved"


    # sudo pip install numpy
    def numpy_image_similarity(self, filepath1, filepath2):
        # TO DO NEED IMPROVEMENT
        #   1. DEAL WITH BLACKGROUND
        #   2. COMPARE PART OF IMAGES

        print "image similarity comparison"
        images = [filepath1, filepath2]
        vectors = []
        norms = []
        for image in images:
            vector = []
            for pixel_tuple in Image.open(image).getdata():
                vector.append(average(pixel_tuple))
            vectors.append(vector)
            norms.append(linalg.norm(vector, 2))
        a, b = vectors
        a_norm, b_norm = norms
        res =dot(a / a_norm, b / b_norm)
        return res

    def adb_tap_to_menu(self) :
        print "cameraHB adb to menu"
        # TO DO : check adb connect before
        os.system("adb shell input tap 360 1150")

    def adb_home(self) :
        print "cameraHB abd tap to home"
        # TO DO : check adb connect before
        os.system("adb shell input keyevent 3")

    def check_alive(self) :
        print "cameraHB check alive"
        img_home = "/tmp/home.jpg"
        img_menu = "/tmp/menu.jpg"

        self.adb_home()
        self.get_single_image(img_home)
        self.adb_tap_to_menu()
        time.sleep(2)
        self.get_single_image_flush_buffer(img_menu)

        similarity = self.numpy_image_similarity(img_home, img_menu)
        print "similarity = %s"%similarity
        if similarity < 0.95 :
            self.ui_state = True
            print "+----------------------+"
            print "+      DEV_ALIVING     +"
            print "+----------------------+"
        else :
            self.ui_state = False
            print "+----------------------+"
            print "+      DEV_CRASHED     +"
            print "+----------------------+"
        self.adb_home()

    def get_ui_state(self) :
        return self.ui_state

if __name__ == '__main__' :
    print "main"
    camhb = cameraHB("/dev/video0", 640, 480)
    camhb.check_alive()
    print "ui_state = %s"%camhb.ui_state
#   camhb.get_single_image("a.jpg")
#   camhb.adb_tap_to_menu()
#   camhb.get_single_image("b.jpg")
#   print camhb.numpy_image_similarity("a.jpg","b.jpg")
#   camhb.adb_home()
