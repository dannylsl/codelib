#!/bin/python

from Tkinter import *
import ttk

root = Tk()
l = ttk.Label(root, text="Starting...")
l.grid()

l.bind('<Enter>', lambda e: l.configure(text='Moved mouse inside'))
l.bind('<Leave>', lambda e: l.configure(text='Moved mouse outside'))
l.bind('<Button-1>',  lambda e: l.configure(text='Clicked Left mouse Button'))
l.bind('<ButtonRelease-1>', lambda e: l.configure(text='Left Button released'))

l.bind('<Button-2>',  lambda e: l.configure(text='Clicked Center mouse Button'))
l.bind('<ButtonRelease-2>', lambda e: l.configure(text='Center Button released'))

l.bind('<Button-3>',  lambda e: l.configure(text='Clicked Right mouse Button'))
l.bind('<ButtonRelease-3>', lambda e: l.configure(text='Right Button released'))

l.bind('<Double-1>', lambda e: l.configure(text='Double clicked'))
l.bind('<B3-Motion>', lambda e: l.configure(text='right Button drag to %d,%d' %(e.x, e.y)))

root.mainloop()
