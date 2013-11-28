#!/bin/bash

from Tkinter import *
import ttk

root = Tk()
root.title("Basic Widgets In python Tkinter")

frame = ttk.Frame(root)

frame['padding'] = (5,10)
frame['borderwidth'] = 2
frame['relief'] = 'sunken'  # flat (default) | raised | sunken | solid | ridge | groove

#frame.columnconfigure(0, weight = 12)
#frame.rowconfigure(0, weight = 1)

frame.grid(column = 0, row = 0, sticky = (N, W, E, S))

l1 = ttk.Label(frame, text='Python Tkinter Basic Widget: Label').grid(column=1, row=1)

resultsContents = StringVar()
l2 = ttk.Label(frame, textvariable = resultsContents).grid(column = 3, row = 3)
resultsContents.set('New value to display')

button = ttk.Button(frame, text='Okay').grid(column = 2, row = 2)



root.mainloop()
