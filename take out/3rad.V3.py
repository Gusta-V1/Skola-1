from turtle import *
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

valda = [" ","","","","","","","","",""]
 
def drag(x,y):
   cirkel(x,y)

def ritadrag(drag, ruta):
    valda[ruta] = drag
    
def fri(ruta):
    return valda[ruta] == " "

def vinnarcheck(valda, drag):
    return
    (valda[1] == drag and valda[2] == drag and valda[3] == drag) or
    (valda[4] == drag and valda[5] == drag and valda[6] == drag) or (valda[7] == drag and valda[8] == drag and valda[9] == drag) or (valda[1] == drag and valda[4] == drag and valda[7] == drag) or (valda[2] == drag and valda[5] == drag and valda[8] == drag) or (valda[3] == drag and valda[6] == drag and valda[9] == drag) or (valda[1] == drag and valda[5] == drag and valda[9] == drag) or (valda[3] == drag and valda[5] == drag and valda[7] == drag)

def full(valda):
    if valda.count(' ') > 1:
        return True
    else:
        return False

def koord(x, y):
    global valda, drag
    print(int(x), int(y))
    grupp = (x+150) // 100
    period = (-y+150) // 100

    ok = True

    if x > -150 and y > 50 and x < -50 and y < 150:
        ruta = 1
    elif x > -50 and y > 50 and x < 50 and y < 150:
        ruta = 2
    elif x > 50 and y > 50 and x < 150 and y < 150:
        ruta = 3
    elif x > -150 and y > -50 and x < -50 and y < 50:
        ruta = 4
    elif x > -50 and y > -50 and x < 50 and y < 50:
        ruta = 5
    elif x > 50 and y > -50 and x < 150 and y < 50:
        ruta = 6
    elif x > -150 and y > -150 and x < -50 and y < 50:
        ruta = 7
    elif x > -50 and y > -150 and x < 50 and y < 50:
        ruta = 8
    elif x > 50 and y > -150 and x < 150 and y < 50:
        ruta = 9
    else:
        ruta = 'ute'
        print('ej i plan')

    print(ruta)
    
    if ruta == 1:
        drag(-100,100)
    elif ruta == 2:
        drag(0,100)
    elif ruta == 3:
        drag(100,100)
    elif ruta == 4:
        drag(-100,0)
    elif ruta == 5:
        drag(0,0)
    elif ruta == 6:
        drag(100,0)
    elif ruta == 7:
        drag(-100,-100)
    elif ruta == 8:
        drag(0,-100)
    elif ruta == 9:
        drag(100,-100)

onscreenclick(koord)
vinnarcheck()
mainloop()

    
