from tkinter import *
from tkinter import messagebox

def visa():
    messagebox.showinfo('Name', 'Du har skrivit: '+ namn.get())

root = Tk()
root.geometry('400x400')
Label(root, text = 'ange namn: ').grid(row=0, column=0)
namn = Entry(root, width = 40)
namn.grid(row = 0, column = 1, columnspan = 5)
b = Button(root, text = 'Knapp', command = visa).grid(row = 1, column = 3)

namn.insert(INSERT, '<skriv namn här>')

root.mainloop()