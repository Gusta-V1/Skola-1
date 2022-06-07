from turtle import *
setworldcoordinates(-200, -200, 200, 200)
ht()
speed(0)
pensize(8)
#color('blue')

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

def spelare (x, y):
    pu()
    goto(x, y)
    fd(25)
    pd()
    circle(25)
    pu()

def dator (x, y):
    goto(x, y)
    rt(45)
    pd()
    for l in range(4):
        fd(50)
        bk(50)
        rt(90)

xclick = 0
yclick = 0

def koord():
    onscreenclick(mus)

def mus(rawx, rawy):
    global xclick
    global yclick
    xclick = int(rawx//1)
    yclick = int(rawy//1)
    print(xclick)
    print(yclick)
    onscreenclick(None)

koord()

if xclick < -50 and yclick < -50:
    print('vn')


