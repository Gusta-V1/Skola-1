from turtle import *
from turtle import write
import random

ht()
setworldcoordinates(0, 0, 350, 150)
speed(0)
pensize(8)

def ritaPlan():
    clear()
    setheading(0)
    pu()
    goto(25, 25)
    pd()
    for i in range(2):
        fd(300)
        lt(90)
        fd(100)
        lt(90)

    pu()
    lt(90)

    goto(125, 25)
    pd()
    fd(100)
    pu()
    goto(225, 25)
    pd()
    fd(100)

    pu()

def spelarDrag(x, y):
    Svald = True
    if 125 > x > 25 and 125 > y > 25:
        Svald = 0
    elif 225 > x > 125 and 125 > y > 25:
        Svald = 1
    elif 325 > x > 225 and 125 > y > 25:
        Svald = 2
    else:
        Svald = 3

    print('Svald = ' +str(Svald))

    Dvald = datorDrag()
    vinnare(Svald, Dvald)

def datorDrag():
    Dvald = True
    Dvald = random.randrange(0, 2, 1)
    print('Dvald = '+str(Dvald))
    return Dvald

def resultatTavla(vinn):

    clear()

    print('vinn = ' +str(vinn))

    vinn = int(vinn)
    
    if vinn == 0:
        goto(50, 100)
        pd()
        write('Oavgjort', font=('Arial, 50'))
        print('if')
    elif vinn == 1:
        goto(50, 100)
        pd()
        write('Spelaren vann', font=('Arial, 50'))
        print('if')
    elif vinn == 2:
        goto(50, 100)
        pd()
        write('Datorn vann', font=('Arial, 50'))
        print('if')
    pu()

    setheading(0)
    pu()
    goto(25, 25)
    pd()
    for i in range(2):
        fd(300)
        lt(90)
        fd(100)
        lt(90)

    pu()
    goto(25, 75)
    pd()
    fd(300)
    pu()

    goto(175, 25)
    pd()
    lt(90)
    fd(50)
    pu()

    goto(40, 50)
    write('Starta om', font=('Arial, 50'))

    goto(200, 50)
    write('Avsluta', font=('Arial, 50'))

    onscreenclick(knapp)

def knapp(x, y):
    if 25 > x > 175 and 75 > y > 25:
        start()
    elif 175 > x > 325 and 75 > y > 25:
        quit()

#0 = oavgjort, 1 = spelare, 2 = dator

def vinnare(Svald, Dvald):
    if Svald == Dvald:
        vinn = 0
    elif Svald == 1 and Dvald == 0:
        vinn = 2
    elif Svald == 2 and Dvald == 0:
        vinn = 1
    elif Svald == 0 and Dvald == 1:
        vinn = 1
    elif Svald == 0 and Dvald == 2:
        vinn = 2
    elif Svald == 2 and Dvald == 1:
        vinn = 2
    elif Svald == 1 and Dvald == 2:
        vinn = 1

    resultatTavla(vinn)

def val(x, y):
    if 25 > x > 175 and 75 > y > 25:
        start()
    elif 300 > x > 175 and 75 > y > 25:
        quit

def start():
    clear()
    goto(0, 0)
    ritaPlan()
    onscreenclick(spelarDrag)

start()
