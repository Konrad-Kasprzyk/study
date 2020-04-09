import random


def pierwiastek(n):
    sum = 0
    i = 0
    while sum <= n:
        i += 1
        sum += 2*i-1
    return i-1


print(pierwiastek(16))



def kompresja(tekst):
    if not tekst:
        return ""

    if len(tekst) == 1:
        return tekst

    tab = list()
    tab.append((tekst[0], 1))
    for i in range(1, len(tekst)):
        if tekst[i-1] != tekst[i]:
            tab.append((tekst[i],1))
        else:
            tab[-1] = (tab[-1][0],tab[-1][1] + 1)

    tekst = ""
    for krotka in tab:
        if krotka[1] == 1:
            tekst += krotka[0]
        else:
            tekst+=str(krotka[1]) + krotka[0]

    return tekst


print(kompresja("aaaaabaaa"))


def dekompresja(tekst):
    dec = ""
    num = 0
    for char in tekst:
        if char.isdigit():
            num = num*10 + int(char)
        else:
            dec += max(num, 1)*char
            num = 0
    return dec


print(dekompresja("12aba3b"))


def foo(text, max_length, n):
    text = list(filter(lambda word: len(word) <= max_length, text.split(' ')))
    to_del = random.sample(text, len(text) - n)
    x = ' '.join(word for word in text if word not in to_del)
    return x


print(foo("Ola ma kota i nietoperza", 4, 3))

