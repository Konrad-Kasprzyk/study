import operator, math, timeit

def pierwsze_imperatywna(n):
    tab = []
    spr = True
    for i in range (2,n):
        spr = True
        for j in range (2,math.floor(math.sqrt(i)) + 1):
            if i % j == 0:
                spr = False
        if spr == True:
            tab.append(i)
    return tab

check = """import math

def pierwsze_imperatywna(n):
    tab = []
    spr = True
    for i in range (2,n):
        spr = True
        for j in range (2,math.floor(math.sqrt(i)) + 1):
            if i % j == 0:
                spr = False
        if spr == True:
            tab.append(i)
    return tab
"""


def pierwsze_skladana(n):
    return [i for i in range(2, n)
     if all(i % j != 0 for j in range(2, math.floor(math.sqrt(i)) + 1))]

check2 = """import math

def pierwsze_skladana(n):
    return [i for i in range(2, n)
     if all(i % j != 0 for j in range(2, math.floor(math.sqrt(i)) + 1))]
"""


def pierwsze_funkcyjna(n):
    return list(filter(lambda i: all(i % j != 0 
    for j in range(2, math.floor(math.sqrt(i)) + 1)), range(2,n)))

check3 = """import math

def pierwsze_funkcyjna(n):
    return list(filter(lambda i: all(i % j != 0 
    for j in range(2, math.floor(math.sqrt(i)) + 1)), range(2,n)))
"""

print(timeit.timeit(setup = check, stmt = "pierwsze_imperatywna(200000)", number = 10))
print(timeit.timeit(setup = check2, stmt = "pierwsze_skladana(200000)", number = 10))
print(timeit.timeit(setup = check3, stmt = "pierwsze_funkcyjna(200000)", number = 10))