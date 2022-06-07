from tkinter import *
from tkinter import messagebox

root = Tk()
root.geometry('1000x1000')

def skrivTill():
    inData = namn.get() + nummer.get()
    #with open('telefonfil.txt', 'a', encoding = 'utf-8') as f:
    f = open('telefonfil.txt', 'a')
    f.write(inData + '\n')
    f.close()
    namn.delete(0, END)
    nummer.delete(0, END)

def visa():

    f = open('telefonfil.txt', 'r+')
    f.truncate(0)

    f = open('telefonfil.txt', 'r')
    for x in f:
        lb.insert(END,x)
        print(x)
    f.close()


    f = open('telefonfil.txt', 'w')
    f.write(''.join(lb.get(0, END)))
    f.write('\n')
    f.close

def taBort():
    #with open('telefonfil.txt', 'a', encoding = 'utf-8') as f:
    lb.delete(ANCHOR)

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
