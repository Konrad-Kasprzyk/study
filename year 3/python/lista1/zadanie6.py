def funkcja(x1,x2,y1,y2):
    sep_main=" "
    for x4 in range(len(str(x2*y2))-2):
            sep_main+=" " 
    
    print(" ",end=sep_main)
    for x in range(x1,x2+1):
        max=len(str(y2*x))
        max = max - len(str(x))
        sep=" "
        for x4 in range(max):
            sep+=" " 
        print(x,end=sep)

    print("")

    for y in range(y1,y2+1):
        if len(str(y))>len(str(y-1)):
            sep_main = sep_main[:-1]
        print(y, end=sep_main)
        for x in range(x1,x2+1):
            max=len(str(y2*x))
            max = max - len(str(x*y))
            sep=" "
            for x4 in range(max):
                sep+=" " 
            print(x*y,end=sep)

        print("")

    return
    


x1 = int(input("podaj x1 "))
x2 = int(input("podaj x2 "))
y1 = int(input("podaj y1 "))
y2 = int(input("podaj y2 "))
funkcja(x1,x2,y1,y2)