#!/bin/python

from Tkinter import *
import ttk

root = Tk()
root.title('Camera Heartbeat')

frame = ttk.Frame(root, width = 640, height = 320)
frame['padding'] = (10, 10, 10, 10)
frame['borderwidth'] = 2
frame['relief'] = 'solid'

frame.grid(column = 0, row = 0)

#image_png = PhotoImage(file = 'png_test.png')
label_img = ttk.Label(frame, borderwidth=10).grid(column = 1, row = 1, columnspan = 4)
#canvas_img = Canvas(frame, bg='black', width = 640, height = 480)
#canvas_img.pack()
#image_png = PhotoImage(file = 'png_test.png')
#canvas_img.create_image(640, 480, image=image_png)


btn_camera = ttk.Button(frame, text='Camera start').grid(column = 0, row = 2)

btn_snip = ttk.Button(frame, text='select area').grid(column = 1, row = 2)

btn_save_config = ttk.Button(frame, text= 'Save config').grid(column = 0, row = 3)
btn_load_config = ttk.Button(frame, text= 'Load config').grid(column = 1, row = 3)

# SUB FRAME
sub_frame = ttk.Frame(frame, relief = 'solid', borderwidth = 3, padding=(10, 10, 10, 10)).grid(column = 2, row = 2, columnspan = 2, rowspan = 2)

chkbtn_grid = ttk.Checkbutton(sub_frame, text='Grid', onvalue='GRID_ON', offvalue='GRID_OFF').grid(column = 0, row = 1)
#
spin_row = StringVar()
spinbox_row = Spinbox(sub_frame, from_ = 3.0, to = 100.0, textvariable = spin_row).grid(column = 1, row = 1)
spin_col = StringVar()
spinbox_col = Spinbox(sub_frame, from_ = 3.0, to = 100.0, textvariable = spin_col).grid(column = 1, row = 2)

sub_frame.pack()

root.mainloop()

