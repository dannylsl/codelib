#!/bin/bash

from Tkinter import *
import ttk

root = Tk()
frame = ttk.Frame(root)

frame['padding'] = (5,10)
frame['borderwidth'] = 2
frame['relief'] = 'sunken'  # flat (default) | raised | sunken | solid | ridge | groove

frame.grid(column = 0, row = 0, sticky = (N, W, E, S))

l1 = ttk.Label(frame, text='Python Tkinter Basic Widget: Label')

root.mainloop()
