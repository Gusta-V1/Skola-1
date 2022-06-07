#Kommentarerna berör rad/programblock under raden som kommentaren står på.

#Importerar nödvändiga bibliotek.
from tkinter import *
from tkinter import messagebox, END, INSERT, scrolledtext

#Test för att se om fil är befintlig eller om en ny fil måste skapas. Filen heter telefonfil.txt
try:
    f = open('telefonfil.txt', 'a')

except:
    f = open('telefonfil.txt', 'w')
    f.close

else:
    f.close

#Tkinter konfigureras, dess geometri och backgrundsfärg.
root = Tk()
root.geometry('460x500')
root.configure(bg = 'grey')

#Funktion för att lägga till nummer och namn i listan.
def läggTill():
    #Slår ihop namn och nummer till en sträng.
    inData = namn.get() + ': ' + nummer.get()
    #Fil öppnas och inData skrivs in.
    with open('telefonfil.txt', 'a', encoding = 'utf-8') as f:
        f.write(inData + '\n')
        lb.insert(END, namn.get() + ': ' + nummer.get())
    #Entry-fönsterna töms.
    namn.delete(0, END)
    nummer.delete(0, END)

#Funktion för att visa/uppdatera listan.
def visa():
    #Fil öppnas.
    attLäggaTill = open('telefonfil.txt', 'r')
    #Tillåter att skrollistan manipuleras.
    lb.config(state = 'normal')
    #Innehåll som skall föras in i skrollista laddas in.
    innehall = attLäggaTill.read()
    #Skrolltext töms på gamla inmatningar.
    lb.delete(1.0, END)
    #Skrolltext populeras.
    lb.insert(END, innehall)
    #Stänger av manipulation av skrolltext.
    lb.config(state = 'disabled')
    #Fil stängs.
    attLäggaTill.close

#Funktion för att ta bort rader från textfil.
def taBort():
    #Namn och nummer slås ihop till en sträng.
    inData = namn.get() + ': ' + nummer.get()
    #Fil öppnas och läses in, stängs därefter.
    with open('telefonfil.txt', 'r', encoding = 'utf-8') as f:
        lines = f.readlines()
    #Fil öppnas och alla rader som INTE uppfyller krav skrivs tillbaka. Vald skrivs ej tillbaka.
    with open('telefonfil.txt', 'w', encoding = 'utf-8') as f:
        for line in lines:
            if line.strip('\n') != inData:
                f.write(line)
    #Entry-fönsterna töms.
    namn.delete(0, END)
    nummer.delete(0, END)

#Text för 'namn' till vänster om entry-fönster.
Label(root, text = 'Namn: ', bg = 'grey').grid(row=0, column=0)
namn = Entry(root, width = 30)
namn.grid(row=0, column=2)

#Text för 'nummer' till vänster om entry-fönster.
Label(root, text = 'Nummer: ', bg = 'grey').grid(row=1, column=0)
nummer = Entry(root, width=30)
nummer.grid(row=1, column=2)

#Knapp för lägg till.
läggTill = Button(root, text='Lägg till', command = läggTill, bg = 'grey')
läggTill.grid(row=3, column=0)

#Knapp för ta bort.
taBort = Button(root, text='Ta bort', command = taBort, bg = 'grey')
taBort.grid(row=3, column=1)

#Knapp för visa.
visa = Button(root, text='Visa/Uppdatera lista', command = visa, bg = 'grey')
visa.grid(row=3, column=2)

#Knapp för att avsluta program.
stop = Button(root, text='Avsluta', command = root.destroy, bg = 'grey')
stop.grid(row=3, column=3)

#Skrollista placeras och konfigureras.
lb = scrolledtext.ScrolledText(root, width=60)
lb.place(x=0, y=100)

#Rader från funktionen visa körs en gång för att populera skrollista vid start av program.
attLäggaTill = open('telefonfil.txt', 'r')
lb.config(state = 'normal')
innehall = attLäggaTill.read()
lb.delete(1.0, END)
lb.insert(END, innehall)
lb.config(state = 'disabled')
attLäggaTill.close

#Programmet loopas för att hållas körande.
root.mainloop()
