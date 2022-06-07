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

def cirkel (x, y):
    pu()
    goto(x, y)
    fd(25)
    pd()
    circle(25)
    pu()

def kryss (x, y):
    goto(x, y)
    rt(45)
    pd()
    for l in range(4):
        fd(50)
        bk(50)
        rt(90)

valda = ["","","","","","","","",""]
drag = "o"

def ritadrag(valda):
    x = -150
    y = 150
    for vald in valda:
        if vald == "o":
            cirkel(x, y)
        elif vald == 'x':
            kryss(x, y)
        x = x + 100
        if x > 50:
            x = -150
            y = y - 200

def koord(x, y):
    global valda, drag
    print(int(x), int(y))
    grupp = (x+150) // 100
    period = (-y+150) // 100
    ruta = grupp + period * 3
    ruta = int(ruta)
    print(grupp, period, ruta)
    valda[ruta] = drag
    if drag == 'o':
        drag = 'x'
    else:
        drag = 'o'
    ritadrag(valda)


onscreenclick(koord)
mainloop()

    
