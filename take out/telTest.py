from tkinter import *
from tkinter import messagebox

root = Tk()
root.geometry('1000x1000')

def Adder():
    enterNumber = number.get()
    f = open('numberFile.txt', 'a', encoding = 'utf-8')
    f.write(enterNumber + '\n')
    f.close()

number = Entry(root, width=20)
number.grid(row=0, column=1)

add = Button(root, text='Add', command = Adder).grid(row=3, column=0)
