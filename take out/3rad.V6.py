from turtle import *
from random import *
setworldcoordinates(-200, -200, 200, 200)
ht()
speed(0)
pensize(8)
#color('blue')

def plan():
    pu()
    goto(-150 , -150)
    pd()
    for i in range(4):
        fd(300)
        lt(90)
    pu()

    goto(-150, -50)
    pd()
    fd(300)
    pu()

    goto(-150, 50)
    pd()
    fd(300)
    pu()

    goto(-50, 150)
    pd()
    rt(90)
    fd(300)
    pu()

    goto(50, 150)
    pd()
    fd(300)
    pu()
    lt(90)

def cirkel (x, y):
    pu()
    goto(x, y)
    rt(90)
    fd(40)
    lt(90)
    pd()
    circle(40)
    pu()

def kryss (x, y):
    goto(x, y)
    rt(45)
    pd()
    for l in range(4):
        fd(50)
        bk(50)
        rt(90)
    pu()
    rt(45)

tagen = [0,0,0,0,0,0,0,0,0]


def spelare(x, y):

    if x > -150 and y > 50 and x < -50 and y < 150:
        ruta = 0
    elif x > -50 and y > 50 and x < 50 and y < 150:
        ruta = 1
    elif x > 50 and y > 50 and x < 150 and y < 150:
        ruta = 2
    elif x > -150 and y > -50 and x < -50 and y < 50:
        ruta = 3
    elif x > -50 and y > -50 and x < 50 and y < 50:
        ruta = 4
    elif x > 50 and y > -50 and x < 150 and y < 50:
        ruta = 5
    elif x > -150 and y > -150 and x < -50 and y < 50:
        ruta = 6
    elif x > -50 and y > -150 and x < 50 and y < 50:
        ruta = 7
    elif x > 50 and y > -150 and x < 150 and y < 50:
        ruta = 8
    else:
        ruta = 9


    if tagen[0] == 0 and ruta == 0:
        kryss(-100, 100)
    elif tagen[1] == 0 and ruta == 1:
        kryss(0, 100)
    elif tagen[2] == 0 and ruta == 2:
        kryss(100, 100)
        
    elif tagen[3] == 0 and ruta == 3:
        kryss(-100, 0)
    elif tagen[4] == 0 and ruta == 4:
        kryss(0, 0)
    elif tagen[5] == 0 and ruta == 5:
        kryss(100, 0)

    elif tagen[6] == 0 and ruta == 6:
        kryss(-100, -100)
    elif tagen[7] == 0 and ruta == 7:
        kryss(0, -100)
    elif tagen[8] == 0 and ruta == 8:
        kryss(100, -100)

    tagen[ruta] = 1
    
    print(ruta)
    print(tagen)
    
def ovinncheck():

    global s

    if tagen[0] == 2 and tagen[1] == 2 and tagen[2] == 2:
        s = 2
    elif tagen[3] == 2 and tagen[4] == 2 and tagen[5] == 2:
        s = 2
    elif tagen[6] == 2 and tagen[7] == 2 and tagen[8] == 2:
        s = 2
    elif tagen[0] == 2 and tagen[3] == 2 and tagen[6] == 2:
        s = 2
    elif tagen[1] == 2 and tagen[4] == 2 and tagen[7] == 2:
        s = 2
    elif tagen[2] == 2 and tagen[5] == 2 and tagen[8] == 2:
        s = 2
    elif tagen[0] == 2 and tagen[4] == 2 and tagen[8] == 2:
        s = 2
    elif tagen[2] == 2 and tagen[4] == 2 and tagen[6] == 2:
        s = 2

    if s == 2:
        print('o vann')
        igenO()

    return s

def xvinncheck():

    global s

#Horisontell
    if tagen[0] == 1 and tagen[1] == 1 and tagen[2] == 1:
        s = 1
    elif tagen[3] == 1 and tagen[4] == 1 and tagen[5] == 1:
        s = 1
    elif tagen[6] == 1 and tagen[7] == 1 and tagen[8] == 1:
        s = 1

#Vertikal
    elif tagen[0] == 1 and tagen[3] == 1 and tagen[6] == 1:
        s = 1
    elif tagen[1] == 1 and tagen[4] == 1 and tagen[7] == 1:
        s = 1
    elif tagen[2] == 1 and tagen[5] == 1 and tagen[8] == 1:
        s = 1

#Diagonal
    elif tagen[0] == 1 and tagen[4] == 1 and tagen[8] == 1:
        s = 1
    elif tagen[2] == 1 and tagen[4] == 1 and tagen[6] == 1:
        s = 1
        
    if s == 1:
        print('x vann')
        igenX()

    return s


def datorn():

    xplacera = randrange(8)

    if xvinncheck() != 1:

    #Horisontellt höger
        if tagen[0] == 1 and tagen[1] == 1:
            xplacera = 2
            
        elif tagen[3] == 1 and tagen[4] == 1:
            xplacera = 5
        elif tagen[6] == 1 and tagen[7] == 1:
            xplacera = 8

    #Horisontellt vänster
        elif tagen[2] == 1 and tagen[1] == 1:
            xplacera = 0
        elif tagen[5] == 1 and tagen[4] == 1:
            xplacera = 3
        elif tagen[8] == 1 and tagen[7] == 1:
            xplacera = 6

    #Vertikalt ner
        elif tagen[0] == 1 and tagen[3] == 1:
            xplacera = 6
        elif tagen[1] == 1 and tagen[4] == 1:
            xplacera = 7
        elif tagen[2] == 1 and tagen[5] == 1:
            xplacera = 8

    #Vertikalt upp
        elif tagen[6] == 1 and tagen[3] == 1:
            xplacera = 0
        elif tagen[7] == 1 and tagen[4] == 1:
            xplacera = 1
        elif tagen[8] == 1 and tagen[5] == 1:
            xplacera = 2

    #I mitten vertikalt
        elif tagen[0] == 1 and tagen[6] == 1:
            xplacera = 3
        elif tagen[1] == 1 and tagen[7] == 1:
            xplacera = 4
        elif tagen[2] == 1 and tagen[8] == 1:
            xplacera = 5

    #I mitten horisontellt
        elif tagen[0] == 1 and tagen[2] == 1:
            xplacera = 1
        elif tagen[3] == 1 and tagen[5] == 1:
            xplacera = 4
        elif tagen[6] == 1 and tagen[8] == 1:
            xplacera = 7

    #Diagonalt höger ner
        elif tagen[0] == 1 and tagen[4] == 1:
            xplacera = 8

    #Diagonalt vänster upp
        elif tagen[8] == 1 and tagen[4] == 1:
            xplacera = 0

    #Diagonalt höger upp
        elif tagen[6] == 1 and tagen[4] == 1:
            xplacera = 2

    #Diagonalt vänster ner
        elif tagen[2] == 1 and tagen[4] == 1:
            xplacera = 6

    #Om mittenrutan är ledig
        elif tagen[4] == 0:
            xplacera = 4


        while tagen[xplacera] != 0:
            xplacera = randrange(8)


        if tagen[0] == 0 and xplacera == 0:
            cirkel(-100, 100)
        elif tagen[1] == 0 and xplacera == 1:
            cirkel(0, 100)
        elif tagen[2] == 0 and xplacera == 2:
            cirkel(100, 100)

        elif tagen[3] == 0 and xplacera == 3:
            cirkel(-100, 0)
        elif tagen[4] == 0 and xplacera == 4:
            cirkel(0, 0)
        elif tagen[5] == 0 and xplacera == 5:
            cirkel(100, 0)

        elif tagen[6] == 0 and xplacera == 6:
            cirkel(-100, -100)
        elif tagen[7] == 0 and xplacera == 7:
            cirkel(0, -100)
        elif tagen[8] == 0 and xplacera == 8:
            cirkel(100, -100)

        tagen[xplacera] = 2

        print('xplacera = ' +str(xplacera))

def igenO():
    clear()
    goto(-100, 100)
    write('O vann', font=('Arial', 100))


def igenX():
    clear()
    goto(-100, 100)
    write('X vann', font=('Arial', 100))
        
def main(x,y):

    spelare(x,y)
    xvinncheck()
    datorn()
    ovinncheck()
    
s = 0

plan()
if s == 0:
    onscreenclick(main)
elif xvinncheck() == 1 or ovinncheck == 2:
    print('ya')
