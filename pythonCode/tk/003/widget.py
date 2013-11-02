from Tkinter import *
import ttk

root = Tk()
button = ttk.Button(root, text = "hello", command="buttonpressed")
button.grid()

button['text'] = 'goodbye'

print button['text']

print button.configure('text')

print button.configure()
