def romb(n):
    ile_haszy=1
    hasze="#"
    przerwa=""

    for x in range (1,n):
        przerwa+=" "

    while ile_haszy<2*n-1:
        print(przerwa,hasze,przerwa,sep='')
        hasze+="##"
        ile_haszy=ile_haszy+2
        przerwa=przerwa[:-1]
    
    while ile_haszy>=1:
        print(przerwa,hasze,przerwa,sep='')
        hasze=hasze[:-2]
        ile_haszy=ile_haszy-2
        przerwa+=" " 
        


ile = int(input("podaj szerokosc rombu: "))
romb(ile)