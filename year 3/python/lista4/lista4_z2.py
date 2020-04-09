import timeit, functools

def doskonale_imperatywna(n):
    tab = []
    sum = 0
    for i in range (2,n):
        sum = 0
        for j in range (1, int(i/2) +1 ):
            if i % j == 0:
                sum += j
        if sum == i:
            tab.append(i)
    return tab

check = """
def doskonale_imperatywna(n):
    tab = []
    sum = 0
    for i in range (2,n):
        sum = 0
        for j in range (1, int(i/2) +1 ):
            if i % j == 0:
                sum += j
        if sum == i:
            tab.append(i)
    return tab
"""

def doskonale_skladana(n):
    return [i for i in range(2, n)
     if i == sum(j for j in range(1,int(i/2) +1)
     if i % j == 0)]

check2="""
def doskonale_skladana(n):
    return [i for i in range(2, n)
     if i == sum(j for j in range(1,int(i/2) +1)
     if i % j == 0)]
"""

def doskonale_funkcyjna(n):
    def pom(i):
        return list(filter(
            lambda j: i%j == 0,
            range(1,int(i/2)+1)))

    return list(filter(
        lambda i: i == functools.reduce(lambda a,b: a + b,pom(i)),
        range(2,n)))

check3="""import functools

def doskonale_funkcyjna(n):
    def pom(i):
        return list(filter(
            lambda j: i%j == 0,
            range(1,int(i/2)+1)))

    return list(filter(
        lambda i: i == functools.reduce(lambda a,b: a + b,pom(i)),
        range(2,n)))


"""

print(timeit.timeit(setup = check, stmt = "doskonale_imperatywna(10000)", number = 10))
print(timeit.timeit(setup = check2, stmt = "doskonale_skladana(10000)", number = 10))
print(timeit.timeit(setup = check3, stmt = "doskonale_funkcyjna(10000)", number = 10))


   