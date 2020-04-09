def wydaj(x):
    count = 0
    while x>=20:
        count=count+1
        x=x-20
    if count>0:
        if count==1:
            print("wydaj 1 banknot 20 złotowy")
        else:
            print("wydaj",count,"banknotów 20 złotowych")
    count = 0

    while x>=10:
        count=count+1
        x=x-10
    if count>0:
        if count==1:
            print("wydaj 1 banknot 10 złotowy")
        else:
            print("wydaj",count,"banknotów 10 złotowych")
    count = 0

    while x>=5:
        count=count+1
        x=x-5
    if count>0:
        if count==1:
            print("wydaj 1 monetę 5 złotową")
        else:
            print("wydaj",count,"monet 5 złotowych")
    count = 0

    while x>=2:
        count=count+1
        x=x-2
    if count>0:
        if count==1:
            print("wydaj 1 monetę 2 złotową")
        else:
            print("wydaj",count,"monet 2 złotowych")
    count = 0

    while x>=1:
        count=count+1
        x=x-1
    if count>0:
        if count==1:
            print("wydaj 1 monetę 1 złotową")
        else:
            print("wydaj",count,"monet 1 złotowych")
    count = 0

ile = int(input("podaj kwote do rozmienienia : "))
wydaj(ile)