#!/bin/bash
from Tkinter import *
import ttk

def btn_click() :
	string = resultsContents.get()
	print string

## b2['state'] == 'disabled'  # REGARD AS FALSE
def toggle_b2_state() :
	global b2
	print "b2['state']={%s}"%b2['state']
	print 'Compara: disabled'
	print b2['state'] == 'disabled'
	if b2['state'] == 'disabled' :
		print 'disabled'

	elif b2['state'] == 'enabled' :
		print 'ENABLED'
#		b2['state'] = 'disabled'


root = Tk()
root.title("Basic Widgets In python Tkinter")

frame = ttk.Frame(root)

frame['padding'] = (10,10, 10, 10)
frame['borderwidth'] = 2
frame['relief'] = 'sunken'  # flat (default) | raised | sunken | solid | ridge | groove

#frame.columnconfigure(0, weight = 12)
#frame.rowconfigure(0, weight = 1)

frame.grid(column = 0, row = 0, sticky = (N, W, E, S))

l1 = ttk.Label(frame, text='Python Tkinter Basic Widget: Label').grid(column=1, row=1)

resultsContents = StringVar()
l2 = ttk.Label(frame, textvariable = resultsContents).grid(column = 3, row = 3)
resultsContents.set('New value to display')

image=PhotoImage(file='python-logo.gif')
l3 = ttk.Label(frame, image=image, anchor='e').grid(column = 1, row = 4, columnspan = 3)

l4 = ttk.Label(root, text="python-logo", justify='left').grid(column = 0, row = 1, sticky='W')

button = ttk.Button(frame, text='Okay', command=btn_click)
button.grid(column = 1, row = 2)
b1 = ttk.Button(frame, text='active', state='!disabeld', command=toggle_b2_state)
b1.grid(column = 2, row = 2)
b2 = ttk.Button(frame, text='stated', state='disabled')
b2.grid(column = 3, row = 2)

root.mainloop()
