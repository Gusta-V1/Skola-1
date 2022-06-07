from turtle import *

speed(9)

pu()
goto(100 ,100)
pd()

setworldcoordinates(-50, -50, 50, 50)

for i in range(4):
    fd(50)
    lt(90)
    fd(10)
    lt(90)
    fd(50)
    rt(90)
