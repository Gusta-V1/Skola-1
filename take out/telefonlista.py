from tkinter import *
from tkinter import messagebox

root = Tk()
root.geometry('1000x1000')

def skrivTill():
    namn = namn.get()
    nummer = nummer.get()
    inData = nummer + ': ' + namn
    #with open('telefonfil.txt', 'a', encoding = 'utf-8') as f:
    f = open('telefonfil.txt', 'a')
    f.write(inData + '\n')
    f.close()
    namn.delete(0, END)
    nummer.delete(0, END)

def visa():
    f = open('telefonfil.txt','r')
    lb.delete(0, END)
    for x in f:
        lb.insert(END,x)
        print(x)
    f.close()

def taBort():
     #with open('telefonfil.txt', 'a', encoding = 'utf-8') as f:
    namn = namn.get()
    nummer = nummer.get()
    inData = nummer + ': ' + namn
    f = open('telefonfil.txt', 'r')
    lines = f.readlines()
    f.close()
    f = open('telefonfil', 'w')
    for line in lines:
        if line.strip('\n') != inData:
            f.write(line)
    f.close()
    #lb.delete(ANCHOR)

Label(root, text = 'Ange nummer: ').grid(row=1, column=0)
nummer = Entry(root, width=30)
nummer.grid(row=1, column=1)

Label(root, text = 'Namn: ').grid(row=0, column=0)
namn = Entry(root, width = 30)
namn.grid(row=0, column=1)

taBort = Button(root, text='Ta bort', command = taBort).grid(row=3, column=0)

läggTill = Button(root, text='Lägg till', command = skrivTill).grid(row=4, column=0)

visaLista = Button(root, text='Visa lista', command = visa).grid(row=5, column=0)

lb = Listbox(root)
lb.grid(row= 6, column=3)

Avsluta = Button(root, text='Avsluta', command = quit).grid(row=6, column=0)

root.mainloop()
