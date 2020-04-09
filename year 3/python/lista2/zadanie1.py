class Wyrazenie():
    def oblicz(self, zmienne):
        return self.val


class Stala(Wyrazenie):
    def __init__(self, x):
        self.val = x
    
    def __str__(self):
        return str(self.val)


class Zmienna(Wyrazenie):
    def __init__(self, x):
        self.val = x
    
    def oblicz(self, zmienne):
        for x in range(len(zmienne)):
            if zmienne[x][0] == self.val:
                return zmienne[x][1]
        raise Exception("brak wartości zmiennej")

    def __str__(self):
        return self.val




class Dodaj(Wyrazenie):
    def __init__(self, L, P):
            self.L = L
            self.P = P

    def oblicz(self, zmienne):
            return self.L.oblicz(zmienne) + self.P.oblicz(zmienne)

    def __str__(self):
        if  isinstance(self.L,(Razy,Dziel)) and isinstance(self.P,(Dodaj,Odejmij)):
            return "(" + self.L.__str__() + ") + " + self.P.__str__()

        elif isinstance(self.P,(Razy,Dziel)) and isinstance(self.L,(Dodaj,Odejmij)):
            return self.L.__str__() + " + (" + self.P.__str__() + ")"

        else:
            return  self.L.__str__() + " + " + self.P.__str__()



class Odejmij(Wyrazenie):
     def __init__(self, L, P):
            self.L = L
            self.P = P

     def oblicz(self, zmienne):
            return self.L.oblicz(zmienne) - self.P.oblicz(zmienne) 

     def __str__(self):
            if  isinstance(self.L,(Razy,Dziel)) and isinstance(self.P,(Dodaj,Odejmij)):
                return "(" + self.L.__str__() + ") - " + self.P.__str__()

            elif isinstance(self.P,(Razy,Dziel)) and isinstance(self.L,(Dodaj,Odejmij)):
                 return self.L.__str__() + " - (" + self.P.__str__() + ")"

            else:
                return  self.L.__str__() + " - " + self.P.__str__()       



class Razy(Wyrazenie):
     def __init__(self, L, P):
            self.L = L
            self.P = P

     def oblicz(self, zmienne):
            return self.L.oblicz(zmienne) * self.P.oblicz(zmienne)

     def __str__(self):
            if  isinstance(self.L,(Razy,Dziel)) and isinstance(self.P,(Razy,Dziel)):
                return self.L.__str__() + " * " + self.P.__str__()

            elif isinstance(self.L,(Stala,Zmienna)) and isinstance(self.P,(Stala,Zmienna)):
                return self.L.__str__() + " * " + self.P.__str__()

            elif isinstance(self.L,(Stala,Zmienna)) or isinstance(self.P,(Dodaj,Odejmij)):
                return  self.L.__str__() + " * (" + self.P.__str__() + ")"
            
            elif isinstance(self.L,(Dodaj,Odejmij)) or isinstance(self.P,(Stala,Zmienna)):
                return  "(" + self.L.__str__() + ") * " + self.P.__str__()

            else:
                return  "(" + self.L.__str__() + ") * (" + self.P.__str__() +")"

class Dziel(Wyrazenie):
     def __init__(self, L, P):
            self.L = L
            self.P = P

     def oblicz(self, zmienne):
            prawa = self.P.oblicz(zmienne)
            if prawa == 0:
                raise Exception("dzielenie przez zero")
            else:
                return self.L.oblicz(zmienne) / self.P.oblicz(zmienne)

     def __str__(self):
            if  isinstance(self.L,(Razy,Dziel)) and isinstance(self.P,(Razy,Dziel)):
                return self.L.__str__() + " / " + self.P.__str__()

            elif isinstance(self.L,(Stala,Zmienna)) and isinstance(self.P,(Stala,Zmienna)):
                return self.L.__str__() + " / " + self.P.__str__()

            elif isinstance(self.L,(Stala,Zmienna)) or isinstance(self.P,(Dodaj,Odejmij)):
                return  self.L.__str__() + " / (" + self.P.__str__() + ")"
            
            elif isinstance(self.L,(Dodaj,Odejmij)) or isinstance(self.P,(Stala,Zmienna)):
                return  "(" + self.L.__str__() + ") / " + self.P.__str__()

            else:
                return  "(" + self.L.__str__() + ") / (" + self.P.__str__() +")"



#sprawdz czy bez metody wykonaj nadal będzie dobrze

class Jezyk():
    def wykonaj(self,zmienne):
        pass

    def __str__(self):
        return ""

class Skip(Jezyk):
    def __str__(self):
        return "pass"

class Comp(Jezyk):
    def __init__(self, L, P):
        self.L = L
        self.P = P
    
    def wykonaj(self, zmienne):
        self.L.wykonaj(zmienne)
        self.P.wykonaj(zmienne)

    def __str__(self):
        return self.L.__str__() + "\n" + self.P.__str__()


class If(Jezyk):
    def __init__(self, wyrazenie,Prawda,Falsz):
        self.wyrazenie = wyrazenie
        self.Prawda = Prawda
        self.Falsz = Falsz
    
    def wykonaj(self, zmienne):
        if self.wyrazenie.oblicz(zmienne) > 0:
            self.Prawda.wykonaj(zmienne)
        else:
            self.Falsz.wykonaj(zmienne)

    def __str__(self):
            return "if(" + self.wyrazenie.__str__() + " > 0){\n" + self.Prawda.__str__() + "\n}else{\n" + self.Falsz.__str__() +"\n}"
        

class While(Jezyk):
    def __init__(self, wyrazenie, Loop):
        self.wyrazenie = wyrazenie
        self.Loop = Loop

    def wykonaj(self, zmienne):
        while self.wyrazenie.oblicz(zmienne):
            self.Loop.wykonaj(zmienne)

    def __str__(self):
            return "while(" + self.wyrazenie.__str__() + " > 0){ \n" + self.Loop.__str__() + "\n}"

class Przypisz(Jezyk):
    def __init__(self, zmienna, wyrazenie):
        self.zmienna = zmienna
        self.wyrazenie = wyrazenie

    def wykonaj(self, zmienne):
        for x in range(len(zmienne)):
            if zmienne[x][0] == self.zmienna.val:
                zmienne[x] = (self.zmienna.val,self.wyrazenie.oblicz(zmienne))
                return
        raise Exception("nie znaleziono zmiennej w Przypisz")

    def __str__(self):
            return str(self.zmienna.val) + " = " + self.wyrazenie.__str__()




t = [("a",0),("b",2),("c",5)]
t2 = [("a",0),("b",2),("c",5)]
t3 = [("a",0),("b",2),("c",5)]

test1 = Comp(If(Stala(1),Przypisz(Zmienna("b"),Stala(44)),Skip()),Przypisz(Zmienna("b"),Stala(443)))
test1.wykonaj(t)
print(t[1])


test2 = Comp(If(Stala(1),Przypisz(Zmienna("b"),Stala(44)),Skip()),Skip())
test2.wykonaj(t2)
print(t2[1])


test3 = While(Zmienna("c"),Comp(Przypisz(Zmienna("c"),Odejmij(Zmienna("c"),Stala(1))),Przypisz(Zmienna("a"),Dodaj(Zmienna("a"),Stala(10)))))
test3.wykonaj(t3)
print(t3[0])


try:
    x = Dziel(Razy(Dodaj(Zmienna("b"), Stala(2)), Zmienna("c")),Stala(0))
    print(x.oblicz(t))

except Exception as x:
    print(x.args[0])

print()

tt = Dodaj(Dodaj(Stala(5),Stala(3)),Razy(Stala(12),Stala(9)))
print(tt)

tt2 = Razy(Dodaj(Stala(5),Stala(3)),Razy(Stala(12),Stala(9)))
print(tt2.__str__())

tt3 = Dziel(Dodaj(tt,tt2),Razy(tt2,tt))
print(tt3.__str__())


print()
print(test1.__str__())
print()
print(test3.__str__())
