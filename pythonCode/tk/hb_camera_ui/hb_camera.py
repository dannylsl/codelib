#!/bin/python

from Tkinter import *
import ttk

import pygame
import pygame.camera
from pygame.locals import *

import thread
import time
from PIL import Image, ImageTk

cam_flag = False

def get_image_cam() :
	global cam_flag, cam_image, cam_imageTk, canvas_img
	print '[THREAD CREATE]get image camera'
	print cam_flag
	while cam_flag :
		image = cam.get_image()
		pygame.image.save(image,'capture.bmp')
		cam_image = Image.open('capture.bmp') 
		cam_imageTk = ImageTk.PhotoImage(cam_image)
		canvas_img.create_image(320, 240, image = cam_imageTk)
		
	print '[THREAD EXIT] get image camera'
	thread.exit_thread()

def cam_start() :
	global cam_flag
	print 'camera start '
	cam.start()
	cam_flag = True
	print cam_flag
	return

def cam_stop() :
	global cam_flag
	print 'camera stop '
	cam.stop()
	cam_flag = False
	print cam_flag
	return

def cam_toggle() :
	print 'cam_toggle called'
	str_btn_camera = var_btn_camera.get()
	if str_btn_camera == 'CAMERA START'	:		
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
canvas_img = Canvas(frame, bg='black', width = 640, height = 480)
canvas_img.pack(side = TOP,expand = YES, fill = BOTH)
#cam_image = Image.open('capture.bmp') 
#cam_imageTk = ImageTk.PhotoImage(cam_image)
#canvas_img.create_image(320, 240, image = cam_imageTk)
canvas_img.grid(column = 0, row = 1, columnspan = 4)

var_btn_camera = StringVar()
btn_camera = ttk.Button(frame,textvariable = var_btn_camera, command = cam_toggle).grid(column = 0, row = 2)
var_btn_camera.set('CAMERA START')

btn_snip = ttk.Button(frame, text='select area').grid(column = 1, row = 2)

btn_save_config = ttk.Button(frame, text= 'Save config').grid(column = 0, row = 3)
btn_load_config = ttk.Button(frame, text= 'Load config').grid(column = 1, row = 3)

chkbtn_grid = ttk.Checkbutton(frame, text='Grid', onvalue='GRID_ON', offvalue='GRID_OFF').grid(column = 2, row = 2)
spin_row = StringVar()
spinbox_row = Spinbox(frame, from_ = 3.0, to = 100.0, textvariable = spin_row).grid(column = 3, row = 2)
spin_col = StringVar()
spinbox_col = Spinbox(frame, from_ = 3.0, to = 100.0, textvariable = spin_col).grid(column = 3, row = 3)

root.mainloop()

