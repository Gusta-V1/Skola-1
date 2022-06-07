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
    drag = 'o'
    pu()
    goto(x, y)
    rt(90)
    fd(40)
    lt(90)
    pd()
    circle(40)
    pu()

def kryss (x, y):
    drag = 'x'
    goto(x, y)
    rt(45)
    pd()
    for l in range(4):
        fd(50)
        bk(50)
        rt(90)
    rt(45)

tagen = [0,0,0,0,0,0,0,0,0]
 
def koord(x, y):
    global valda, drag
    print(int(x), int(y))
    grupp = (x+150) // 100
    period = (-y+150) // 100

    ok = True

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
        ruta = 'ute'
        print('ej i plan')

    tagen[ruta] = 1

    vinncheck()

    print(ruta)
    print(tagen)

def vinncheck():
    global s
    s = True
    if tagen[0] == 1 and tagen[1] == 1 and tagen[2] == 1:
        s = 1
    elif tagen[3] == 1 and tagen[4] == 1 and tagen[5] == 1:
        s = 1
    elif tagen[6] == 1 and tagen[7] == 1 and tagen[8] == 1:
        s = 1
    elif tagen[0] == 1 and tagen[3] == 1 and tagen[6] == 1:
        s = 1
    elif tagen[1] == 1 and tagen[4] == 1 and tagen[7] == 1:
        s = 1
    elif tagen[2] == 1 and tagen[5] == 1 and tagen[8] == 1:
        s = 1
    elif tagen[1] == 1 and tagen[5] == 1 and tagen[9] == 1:
        s = 1
    elif tagen[3] == 1 and tagen[5] == 1 and tagen[6] == 1:
        s = 1
    else: s = 0

    if s == 1:
        print('s vann')

def datorn():
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

#Annars placera slumpmässigt
    else:
        randrange(8)

plan()
onscreenclick(koord)
mainloop()
