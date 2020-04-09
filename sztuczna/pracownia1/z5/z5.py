# coding: utf-8

import random

def prepareTable():
    file = open("zad5_input.txt", encoding='utf-8')
    s = file.readline()
    r = int(s[0]) # rows
    c = int(s[2]) # columns
    T = [False]*(r+1)
    for i in range(r+1): 
        T[i]=[False]*(c+1)

    for i in range(1, r+1): 
        T[i][0] = int(file.readline())
      
    for i in range(1, c+1):
        T[0][i] = int(file.readline())

    for i in range(1, r+1):
        for j in range(1, c+1):
            T[i][j] = bool(random.randint(0, 1))
    return T, r, c


def countBits(L):
    b=0
    for i in range(len(L)):
        if L[i]:
            b+=1
    return b

# ret -1 if no good change after bit insert, ret bits/goal otherwise -> fulfillment state
def calcChange(L, bit_index):
    goal = L[0]
    mostBits = 0
    mostBits_after = 0
    for i in range(1, len(L)-goal + 1):
        bits = countBits(L[i:i+goal])
        if mostBits < bits:
            mostBits = bits

    L[bit_index] = not L[bit_index]
    for i in range(1, len(L)-goal + 1):
        bits = countBits(L[i:i+goal])
        if mostBits_after < bits:
            mostBits_after = bits

    L[bit_index] = not L[bit_index]
    if L[bit_index]:
        if mostBits > mostBits_after:
            return -1
        else:
            return mostBits_after/goal
    else:
        if mostBits >= mostBits_after:
            return -1
        else:
            return mostBits_after/goal


def makeLine(T, column, rows):
    L=[]
    for i in range(rows + 1):
        L.append(T[i][column])
    return L


def doneLine(L):
    goal = L[0]
    if countBits(L[1:]) != goal:
        return False
    for j in range(1, len(L)-goal + 1):
        if L[j] == True:
            if countBits(L[j:j+goal]) != goal:
                return False
            break
    return True


def finished(T, r, c):
    for i in range(1, r+1):
        if not doneLine(T[i]):
            return False
    for i in range(1, c+1):
        L = makeLine(T, i, r)
        if not doneLine(L):
            return False
    return True


def alg(T, r, c):
    iter = 0
    undone_r = []
    undone_c = []
    for i in range(1, r+1):
        if not doneLine(T[i]):
            undone_r.append(i)
    for i in range(1, c+1):
        if not doneLine(makeLine(T, i, r)):
            undone_c.append(i)
    while not finished(T, r, c):
        # small chance for bad change
        if random.randint(1,50) == 50:
            i = random.randint(1,r)
            j = random.randint(1,c)
            T[i][j] = not T[i][j]

            L = makeLine(T, j, r)
            if j in undone_c:
                if doneLine(L):
                    undone_c.remove(j)
            else:
                if not doneLine(L):
                    undone_c.append(j)
            
            if i in undone_r:
                if doneLine(T[i]):
                    undone_r.remove(i)
            else:
                if not doneLine(T[i]):
                    undone_r.append(i)
            continue
        #changing row
        if undone_r and (not undone_c or random.randint(0, 1) == 0):
            chosen = random.choice(undone_r)
            good_changes = []
            for i in range(1, c+1):
                change_rate = calcChange(T[chosen], i)
                if change_rate > 0:
                    good_changes.append(i)
            best = -1
            best_idx = 1
            for i in good_changes:
                L = makeLine(T, i, r)
                curr = calcChange(L, chosen)
                if curr > best:
                    best = curr
                    best_idx = i
            if best == -1:
                best_idx = random.choice(good_changes)
            T[chosen][best_idx] = not T[chosen][best_idx]
            # checking if change made row or column done/undone
            if doneLine(T[chosen]):
                undone_r.remove(chosen)
            L = makeLine(T, best_idx, r)
            if best_idx in undone_c:
                if doneLine(L):
                    undone_c.remove(best_idx)
            else:
                if not doneLine(L):
                    undone_c.append(best_idx)

        #changing column
        elif undone_c:
            chosen = random.choice(undone_c)
            L = makeLine(T, chosen, r)
            good_changes = []
            for i in range(1, r+1):
                change_rate = calcChange(L, i)
                if change_rate > 0:
                    good_changes.append(i)
            best = -1
            best_idx = 1
            for i in good_changes:
                curr = calcChange(T[i], chosen)
                if curr > best:
                    best = curr
                    best_idx = i
            if best == -1:
                best_idx = random.choice(good_changes)
            T[best_idx][chosen] = not T[best_idx][chosen]
            L[best_idx] = not L[best_idx]
            # checking if change made row or column done/undone
            if doneLine(L):
                undone_c.remove(chosen)
            if best_idx in undone_r:
                if doneLine(T[best_idx]):
                    undone_r.remove(best_idx)
            else:
                if not doneLine(T[best_idx]):
                    undone_r.append(best_idx)
                    
        iter += 1
        if iter == 100:
            T, r, c = prepareTable()
            iter = 0
            undone_r = []
            undone_c = []
            for i in range(1, r+1):
                if not doneLine(T[i]):
                    undone_r.append(i)
            for i in range(1, c+1):
                if not doneLine(makeLine(T, i, r)):
                    undone_c.append(i)
    return T


def result(T, r, c):
    output = open("zad5_output.txt", "w+", encoding='utf-8')
    
    for i in range(1, c+1):
        line = ""
        for j in range(1, r+1):
            if T[i][j] == 1:
                line = line + "#"
            else:
                line = line + "."
        output.write(line)
        output.write("\n")

T, r, c = prepareTable()
T = alg(T, r, c)
result(T, r, c)