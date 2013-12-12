#!/bin/python

import pygame
import pygame.camera
from pygame.locals import *

import os

class cameraHB() :
    mutex = None
    cam = None
    size_width = 0
    size_height = 0
    device = ""


    def __init__(self, dev = "/dev/video0", size_w = 640, size_h = 480) :
        self.size_width = size_w
        self.size_height= size_h
        self.dev        = dev

        pygame.init()
        pygame.camera.init()
        self.cam = pygame.camera.Camera(self.dev, (self.size_width, self.size_height))


if __name__ == '__main__' :
    print "main"
    camhb = cameraHB("/dev/video1", 640, 480)


