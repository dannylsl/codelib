#!/bin/python

from Tkinter import *
import ttk
import tkMessageBox

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
    # print cam_flag
    # print " 000 cam_imageTk id= %s"%id(cam_imageTk)
    while cam_flag :
        image = cam.get_image()
        pygame.image.save(image,'capture.bmp')
        cam_image = Image.open('capture.bmp')
        cam_imageTk = ImageTk.PhotoImage(cam_image)
        canvas_img.create_image(0, 0, anchor = NW ,image = cam_imageTk)
        ## It seem the statement as below could solve the Blink problem
        ## As for the reason, not catch now
        # print "PRE cam_imageTk id= %s"%id(cam_imageTk)
        # time.sleep(3)
        obr = cam_imageTk

    print '[THREAD EXIT] get image camera'
    thread.exit_thread()

def get_single_image() :
    global cam
    image = cam.get_image()
    image = cam.get_image()
    image = cam.get_image()
    image_name = "%s.jpg"%time.time()
    pygame.image.save(image,image_name)
    print "IMAGE SAVED: %s"%image_name


def cam_start() :
    global cam,cam_flag
    print 'camera start '
    cam.start()
    cam_flag = True
    # print cam_flag
    btn_get_image['state'] = 'enabled'
    return


def cam_stop() :
    global cam,cam_flag
    print 'camera stop '
    cam.stop()
    cam_flag = False
    # print cam_flag
    btn_get_image['state'] = 'disabled'
    return


def cam_toggle() :
    print 'cam_toggle called'
    str_btn_camera = var_btn_camera.get()

    if video_dev.get() != "" :
        if str_btn_camera == 'CAMERA START' :
            cam_start()
            thread.start_new_thread(get_image_cam, ())
            var_btn_camera.set('CAMERA STOP')

        elif str_btn_camera == 'CAMERA STOP' :
            cam_stop()
            var_btn_camera.set('CAMERA START')
    else :
        tkMessageBox.showinfo("Attention","Select camera device")


def find_device() :
    print 'find_device called'
    rootDir = '/dev/'
    dev_list = []
    for file in os.listdir(rootDir) :
        if 'video' in file :
            print file
            path = os.path.join(rootDir, file)
            dev_list.append(path)
    return dev_list


def deivce_changed(*args) :
    global cam
    print 'device_changed'
    print video_dev.get(), "selected"
    cam = pygame.camera.Camera(video_dev.get(), (640,480))


def canvas_lmouse_click(event) :
    global start_x, start_y
    # print "canvas_lmouse_click called"
    # print "CLICK x=%s\ty=%s"%(event.x, event.y)
    start_x = event.x
    start_y = event.y


def draw_rect(event) :
    global start_x, start_y
    global canvas_img
    # print "draw event called"
    # print "x=%s\ty=%s"%(event.x, event.y)
    # set the background
    canvas_img.create_image(0, 0, anchor=NW, image = cam_imageTk)
    canvas_img.create_rectangle((start_x, start_y, event.x, event.y), outline="white", width=2)


def canvas_lmouse_release(event) :
    global start_x, start_y
    global end_x, end_y
    global canvas_img
    # print "canvas_lmouse_release called"
    # print "RELEASE x=%s\ty=%s"%(event.x, event.y)
    end_x = event.x
    end_y = event.y


if __name__ == '__main__' :

    start_x = 0
    start_y = 0
    end_x = 0
    end_y = 0

    pygame.init()
    pygame.camera.init()
#    cam = pygame.camera.Camera('/dev/video2', (640,480))

    devices = find_device()

    root = Tk()
    root.title('Camera Heartbeat')

    frame = ttk.Frame(root)
    frame['padding'] = (10, 10, 10, 10)
    frame['borderwidth'] = 5
    frame['relief'] = 'solid'

    canvas_img = Canvas(frame,bg='black', width = 640, height = 480)
    canvas_img.pack(side = TOP,expand = YES, fill = BOTH)

    canvas_img.bind('<ButtonPress-1>', canvas_lmouse_click)
    canvas_img.bind('<B1-Motion>', draw_rect)
    canvas_img.bind('<ButtonRelease-1>', canvas_lmouse_release)

    if os.path.exists('capture.bmp') == True :
        cam_image = Image.open('capture.bmp')
        cam_imageTk = ImageTk.PhotoImage(cam_image)
        canvas_img.create_image(0, 0, anchor=NW, image = cam_imageTk)
    else :
        pass

    video_dev = StringVar()
    combox = ttk.Combobox(frame, textvariable = video_dev)
    combox['values'] = devices
    combox.bind('<<ComboboxSelected>>',deivce_changed)

    var_btn_camera = StringVar()
    btn_camera = ttk.Button(frame,textvariable = var_btn_camera, command = cam_toggle)
    var_btn_camera.set('CAMERA START')


    btn_snip = ttk.Button(frame, text='select area')

    btn_save_config = ttk.Button(frame, text = 'Save config')
    btn_load_config = ttk.Button(frame, text = 'Load config')

    chkbtn_grid = ttk.Checkbutton(frame, text = 'Grid', onvalue = 'GRID_ON', offvalue = 'GRID_OFF')

    spin_row = StringVar()
    spinbox_row = Spinbox(frame, from_ = 3.0, to = 100.0, textvariable = spin_row)
    spin_col = StringVar()
    spinbox_col = Spinbox(frame, from_ = 3.0, to = 100.0, textvariable = spin_col)

    btn_get_image = ttk.Button(frame, text = "Get Image", state = 'disabled' ,command = get_single_image)

    ### GRID POSITION  ###
    #--------------------#
    frame.grid(column = 0, row = 0)
    canvas_img.grid(column = 0, row = 1, columnspan = 5)

    combox.grid(column = 0 , row = 2)
    btn_camera.grid(column = 1, row = 2)
    btn_snip.grid(column = 2, row = 2)
    btn_save_config.grid(column = 1, row = 3)
    btn_load_config.grid(column = 2, row = 3)
    chkbtn_grid.grid(column = 3, row = 2)
    spinbox_row.grid(column = 4, row = 2)
    spinbox_col.grid(column = 4, row = 3)
    btn_get_image.grid(column = 3, row = 3)

    root.mainloop()
