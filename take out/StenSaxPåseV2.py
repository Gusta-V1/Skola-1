from turtle import *
import random

ht()
setworldcoordinates(0, 0, 350, 150)
speed(0)
pensize(8)

def ritaPlan():
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

    return Svald

    onscreenclick(resultatTavla)

def datorDrag():
    Dvald = random.randrange(0, 2, 1)
    print('Dvald = '+str(Dvald))
    return Dvald

def resultatTavla():
    clear()
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

#0 = oavgjort, 1 = spelare, 2 = dator

def vinnare():
    
    if spelarDrag() == datorDrag():
        vinn = 0
    elif spelarDrag() == 1 and datorDrag() == 0:
        vinn = 2
    elif spelarDrag() == 2 and datorDrag() == 0:
        vinn = 1
    elif spelarDrag() == 0 and datorDrag() == 1:
        vinn = 1
    elif spelarDrag() == 0 and datorDrag() == 2:
        vinn = 2
    elif spelarDrag() == 2 and datorDrag() == 1:
        vinn = 2
    elif spelarDrag() == 1 and datorDrag() == 2:
        vinn = 1

    print(vinn)

def main():
    ritaPlan()
    onscreenclick(spelarDrag)
    datorDrag()
    vinnare()

    
main()
mainloop()
