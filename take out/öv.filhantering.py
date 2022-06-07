f = open('testfil.txt', 'w')
rad = input('Skriv 1' )
while rad:
    f.write(rad+'\n')
    rad = input('Skriv 2' )
f.close

f = open('testfil.txt', 'r')
rad = f.readline()

while rad:
    print(rad, end=' ')
    rad = f.readline()
f.close
