import operator, math, timeit, itertools
from prettytable import PrettyTable

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
  

def pierwsze_skladana(n):
    return [i for i in range(2, n)
     if all(i % j != 0 for j in range(2, math.floor(math.sqrt(i)) + 1))]


def pierwsze_funkcyjna(n):
    return list(filter(lambda i: all(i % j != 0 
    for j in range(2, math.floor(math.sqrt(i)) + 1)), range(2,n)))


def isPrime(n):
    if n <= 1:
        return False
    for i in range(2, math.floor(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True


def pierwsze_iterator():
    i = itertools.count(2)
    while(True):
        p = next(i)
        if(isPrime(p)):
            yield p


def lista_od_iteratora(n):
    p = pierwsze_iterator()
    tab = []
    for x in range(n):
        tab.append(next(p))
    return tab


setup = '''
import math
from __main__ import pierwsze_imperatywna, pierwsze_skladana, pierwsze_funkcyjna, isPrime, pierwsze_iterator,lista_od_iteratora
n = 100
n2 = 1000
n3 = 5000
n4 = 100000
'''

pierwsze_imperatywna_test = "pierwsze_imperatywna(n)"
pierwsze_skladana_test = "pierwsze_skladana(n)"
pierwsze_funkcyjna_test = "pierwsze_funkcyjna(n)"
pierwsze_iterator_test = "lista_od_iteratora(n)"

pierwsze_imperatywna_test_2 = "pierwsze_imperatywna(n2)"
pierwsze_skladana_test_2 = "pierwsze_skladana(n2)"
pierwsze_funkcyjna_test_2 = "pierwsze_funkcyjna(n2)"
pierwsze_iterator_test_2 = "lista_od_iteratora(n2)"

pierwsze_imperatywna_test_3 = "pierwsze_imperatywna(n3)"
pierwsze_skladana_test_3 = "pierwsze_skladana(n3)"
pierwsze_funkcyjna_test_3 = "pierwsze_funkcyjna(n3)"
pierwsze_iterator_test_3 = "lista_od_iteratora(n3)"

pierwsze_imperatywna_test_4 = "pierwsze_imperatywna(n4)"
pierwsze_skladana_test_4 = "pierwsze_skladana(n4)"
pierwsze_funkcyjna_test_4 = "pierwsze_funkcyjna(n4)"
pierwsze_iterator_test_4 = "lista_od_iteratora(n4)"


t_imperatywna= timeit.timeit(setup = setup, stmt = pierwsze_imperatywna_test, number = 10)
t_skladana= timeit.timeit(setup = setup, stmt = pierwsze_skladana_test, number = 10)
t_funkcyjna= timeit.timeit(setup = setup, stmt = pierwsze_funkcyjna_test, number = 10)
t_iterator= timeit.timeit(setup = setup, stmt = pierwsze_iterator_test, number = 10)

t_imperatywna_2= timeit.timeit(setup = setup, stmt = pierwsze_imperatywna_test_2, number = 10)
t_skladana_2= timeit.timeit(setup = setup, stmt = pierwsze_skladana_test_2, number = 10)
t_funkcyjna_2= timeit.timeit(setup = setup, stmt = pierwsze_funkcyjna_test_2, number = 10)
t_iterator_2= timeit.timeit(setup = setup, stmt = pierwsze_iterator_test_2, number = 10)

t_imperatywna_3= timeit.timeit(setup = setup, stmt = pierwsze_imperatywna_test_3, number = 10)
t_skladana_3= timeit.timeit(setup = setup, stmt = pierwsze_skladana_test_3, number = 10)
t_funkcyjna_3= timeit.timeit(setup = setup, stmt = pierwsze_funkcyjna_test_3, number = 10)
t_iterator_3= timeit.timeit(setup = setup, stmt = pierwsze_iterator_test_3, number = 10)

t_imperatywna_4= timeit.timeit(setup = setup, stmt = pierwsze_imperatywna_test_4, number = 10)
t_skladana_4= timeit.timeit(setup = setup, stmt = pierwsze_skladana_test_4, number = 10)
t_funkcyjna_4= timeit.timeit(setup = setup, stmt = pierwsze_funkcyjna_test_4, number = 10)
t_iterator_4= timeit.timeit(setup = setup, stmt = pierwsze_iterator_test_4, number = 10)

results_table = PrettyTable()

results_table.field_names = ["N", "imperatywna",
                             "skladana", "funkcyjna", "iterator"]

results_table.add_row(
    ["100", t_imperatywna, t_skladana, t_funkcyjna, t_iterator])
results_table.add_row(
    ["1000", t_imperatywna_2, t_skladana_2, t_funkcyjna_2, t_iterator_2])
results_table.add_row(
    ["5000", t_imperatywna_3, t_skladana_3, t_funkcyjna_3, t_iterator_3])
results_table.add_row(
    ["10000", t_imperatywna_4, t_skladana_4, t_funkcyjna_4, t_iterator_4])

print(results_table)



