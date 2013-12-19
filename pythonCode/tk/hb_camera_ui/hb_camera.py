#!/bin/python

from Tkinter import *
import ttk

import pygame
import pygame.camera
from pygame.locals import *

import thread
import time
import os
from PIL import Image, ImageTk

cam_flag = False

def get_image_cam() :
    global cam,cam_flag,cam_image, cam_imageTk, canvas_img
    print '[THREAD CREATE]get image camera'
#   print cam_flag
#    print " 000 cam_imageTk id= %s"%id(cam_imageTk)
    while cam_flag :
        image = cam.get_image()
        pygame.image.save(image,'capture.bmp')
        cam_image = Image.open('capture.bmp')
        cam_imageTk = ImageTk.PhotoImage(cam_image)
        canvas_img.create_image(0, 0, anchor = NW ,image = cam_imageTk)
        ## It seem the statement as below could solve the Blink problem
        ## As for the reason, not catch now
#        print "PRE cam_imageTk id= %s"%id(cam_imageTk)
#        time.sleep(3)
        obr = cam_imageTk
#        print cam_imageTk.__dict__
#        print "AFT cam_imageTk id= %s"%id(cam_imageTk)
#        print "obr id=%s"%id(obr)

    print '[THREAD EXIT] get image camera'
    thread.exit_thread()

def get_single_image() :
    global cam
    image = cam.get_image()
    image_name = "%s.jpg"%time.time()
    pygame.image.save(image,image_name)
    print "IMAGE SAVED: %s"%image_name

def cam_start() :
    global cam,cam_flag
    print 'camera start '
    cam.start()
    cam_flag = True
#   print cam_flag
    btn_get_image['state'] = 'enabled'
    return

def cam_stop() :
    global cam,cam_flag
    print 'camera stop '
    cam.stop()
    cam_flag = False
#   print cam_flag
    btn_get_image['state'] = 'disabled'
    return

def cam_toggle() :
    print 'cam_toggle called'
    str_btn_camera = var_btn_camera.get()
    if str_btn_camera == 'CAMERA START' :
        cam_start()
        thread.start_new_thread(get_image_cam, ())
        var_btn_camera.set('CAMERA STOP')

    elif str_btn_camera == 'CAMERA STOP' :
        cam_stop()
        var_btn_camera.set('CAMERA START')

pygame.init()
pygame.camera.init()
cam = pygame.camera.Camera("/dev/video0", (640,480))

root = Tk()
root.title('Camera Heartbeat')

frame = ttk.Frame(root)
frame['padding'] = (10, 10, 10, 10)
frame['borderwidth'] = 5
frame['relief'] = 'solid'

frame.grid(column = 0, row = 0)

#image_png = PhotoImage(file = 'png_test.png')
#label_img = ttk.Label(frame, borderwidth=10).grid(column = 1, row = 1, columnspan = 4)
canvas_img = Canvas(frame,bg='black', width = 640, height = 480)
canvas_img.pack(side = TOP,expand = YES, fill = BOTH)
if os.path.exists('capture.bmp') == True :
    cam_image = Image.open('capture.bmp') 
    cam_imageTk = ImageTk.PhotoImage(cam_image)
    canvas_img.create_image(0, 0, anchor=NW, image = cam_imageTk)
else :
    pass

canvas_img.grid(column = 0, row = 1, columnspan = 4)

var_btn_camera = StringVar()
btn_camera = ttk.Button(frame,textvariable = var_btn_camera, command = cam_toggle).grid(column = 0, row = 2)
var_btn_camera.set('CAMERA START')

btn_snip = ttk.Button(frame, text='select area').grid(column = 1, row = 2)

btn_save_config = ttk.Button(frame, text = 'Save config').grid(column = 0, row = 3)
btn_load_config = ttk.Button(frame, text = 'Load config').grid(column = 1, row = 3)

chkbtn_grid = ttk.Checkbutton(frame, text = 'Grid', onvalue = 'GRID_ON', offvalue = 'GRID_OFF').grid(column = 2, row = 2)
spin_row = StringVar()
spinbox_row = Spinbox(frame, from_ = 3.0, to = 100.0, textvariable = spin_row).grid(column = 3, row = 2)
spin_col = StringVar()
spinbox_col = Spinbox(frame, from_ = 3.0, to = 100.0, textvariable = spin_col).grid(column = 3, row = 3)

btn_get_image = ttk.Button(frame, text = "Get Image", state = 'disabled' ,command = get_single_image)
btn_get_image.grid(column = 2, row = 3)

root.mainloop()
