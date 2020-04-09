# coding: utf-8

import random

def randomizeTable(T, r, c):
    for i in range(1, r+1):
        for j in range(1, c+1):
            T[i][j] = bool(random.randint(0, 1))


def prepareTable():
    file = open("zad_input.txt", encoding='utf-8')
    line = file.readline()
    space = 0
    for i in range(len(line)):
        if line[i] == ' ':
            space = i
            break
    r = int(line[:space]) # rows
    c = int(line[space+1:]) # columns
    T = [False]*(r+1)
    for i in range(r+1): 
        T[i]=[False]*(c+1)

    for i in range(1, r+1): 
        T[i][0] = []
        line = file.readline()
        last_j = 0
        for j in range(len(line)):
            if line[j] == ' ' or line[j] == '\n':
                T[i][0].append(int(line[last_j:j]))
                last_j = j + 1
            elif j+1 == len(line):
                T[i][0].append(int(line[last_j:j+1]))
      
    for i in range(1, c+1):
        T[0][i] = []
        line = file.readline()
        last_j = 0
        for j in range(len(line)):
            if line[j] == ' ' or line[j] == '\n':
                T[0][i].append(int(line[last_j:j]))
                last_j = j + 1
            elif j+1 == len(line):
                T[0][i].append(int(line[last_j:j+1]))
    randomizeTable(T, r, c)
    return T, r, c


def countBits(L):
    b=0
    for i in range(len(L)):
        if L[i]:
            b+=1
    return b

# ret -1 if no good change after bit insert, ret bits/goal otherwise -> fulfillment state
def calcChange(L, bit_index, curr_fulf_ratio):
    L[bit_index] = not L[bit_index]
    fulf_ratio_after = calcFulfRatio(L)
    L[bit_index] = not L[bit_index]
    if L[bit_index]:
        if curr_fulf_ratio > fulf_ratio_after:
            return -1
        else:
            return fulf_ratio_after
    else:
        if curr_fulf_ratio >= fulf_ratio_after:
            return -1
        else:
            return fulf_ratio_after


# ret fulfillment state -> most turned bits/goal in line
def calcFulfRatio(L):
    block_lines = []
    for block_nr in range(len(L[0])):
        block_lines.append([])
        for i in range( sum(L[0][:block_nr]) + len(L[0][:block_nr]) + 1,
                        len(L) - (sum(L[0][block_nr:]) + len(L[0][block_nr+1:])) + 1):
            block_lines[block_nr].append(countBits(L[i:i+L[0][block_nr]])/L[0][block_nr])
    return(calcCurrFulf(block_lines, 0, 0, len(L[0]) - 1))

# block_lines[block_nr][pos_in_line] - for given block fulfillment % in particular position in line
def calcCurrFulf(block_lines, start_iter, rec_depth, max_rec_depth):
    curr_total_max = -1
    curr_block_max = -1
    L = block_lines[rec_depth]
    for i in range(start_iter, len(L)):
        if L[i] < curr_block_max:
            continue
        else:
            curr_block_max = L[i]
        next_blocks_total_max = 0
        if rec_depth < max_rec_depth:
            next_blocks_total_max = calcCurrFulf(block_lines, i, rec_depth + 1, max_rec_depth)   
        potential_total_max = curr_block_max + next_blocks_total_max
        if potential_total_max > curr_total_max:
            curr_total_max = potential_total_max
    return curr_total_max


def makeLine(T, column, rows):
    L=[]
    for i in range(rows + 1):
        L.append(T[i][column])
    return L


def doneLine(L):
    goal = sum(L[0])
    if countBits(L[1:]) != goal:
        return False
    if calcFulfRatio(L) != len(L[0]):
        return False
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
    fulf_ratio_r = [0]*(r+1)
    fulf_ratio_c = [0]*(c+1)
    undone_r = []
    undone_c = []
    for i in range(1, r+1):
        if not doneLine(T[i]):
            undone_r.append(i)
        fulf_ratio_r[i] = calcFulfRatio(T[i])
    for i in range(1, c+1):
        if not doneLine(makeLine(T, i, r)):
            undone_c.append(i)
        L = makeLine(T, i, r)
        fulf_ratio_c[i] = calcFulfRatio(L)
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
            fulf_ratio_c[j] = calcFulfRatio(L)
            
            if i in undone_r:
                if doneLine(T[i]):
                    undone_r.remove(i)
            else:
                if not doneLine(T[i]):
                    undone_r.append(i)
            fulf_ratio_r[i] = calcFulfRatio(T[i])
            continue
        #changing row
        if undone_r and (not undone_c or random.randint(0, 1) == 0):
            chosen = random.choice(undone_r)
            good_changes = []
            for i in range(1, c+1):
                change_rate = calcChange(T[chosen], i, fulf_ratio_r[chosen])
                if change_rate > 0:
                    good_changes.append(i)
            best = -1
            best_idx = 1
            for i in good_changes:
                L = makeLine(T, i, r)
                curr = calcChange(L, chosen, fulf_ratio_c[i])
                if curr > best:
                    best = curr
                    best_idx = i
            if best == -1:
                best_idx = random.choice(good_changes)
            T[chosen][best_idx] = not T[chosen][best_idx]
            # checking if change made row or column done/undone
            if doneLine(T[chosen]):
                undone_r.remove(chosen)
                fulf_ratio_r[chosen] = len(T[chosen][0])
            else:
                fulf_ratio_r[chosen] = calcFulfRatio(T[chosen])
            L = makeLine(T, best_idx, r)
            if best_idx in undone_c:
                if doneLine(L):
                    undone_c.remove(best_idx)
                    fulf_ratio_c[best_idx] = len(L[0])
                else:
                    fulf_ratio_c[best_idx] = calcFulfRatio(L)
            else:
                if not doneLine(L):
                    undone_c.append(best_idx)
                    fulf_ratio_c[best_idx] = calcFulfRatio(L)

        #changing column
        elif undone_c:
            chosen = random.choice(undone_c)
            L = makeLine(T, chosen, r)
            good_changes = []
            for i in range(1, r+1):
                change_rate = calcChange(L, i, fulf_ratio_c[chosen])
                if change_rate > 0:
                    good_changes.append(i)
            best = -1
            best_idx = 1
            for i in good_changes:
                curr = calcChange(T[i], chosen, fulf_ratio_r[i])
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
                fulf_ratio_c[chosen] = len(L[0])
            else:
                fulf_ratio_c[chosen] = calcFulfRatio(L)

            if best_idx in undone_r:
                if doneLine(T[best_idx]):
                    undone_r.remove(best_idx)
                    fulf_ratio_r[best_idx] = len(T[best_idx][0])
                else:
                    fulf_ratio_r[best_idx] = calcFulfRatio(T[best_idx])
            else:
                if not doneLine(T[best_idx]):
                    undone_r.append(best_idx)
                    fulf_ratio_r[best_idx] = calcFulfRatio(T[best_idx])
                    
        iter += 1
        if iter == 3000:
            print("reset")
            return (T, False)
    return (T, True)


def result(T, r, c):
    output = open("zad_output.txt", "w+", encoding='utf-8')
    for i in range(1, r+1):
        line = ""
        for j in range(1, c+1):
            if T[i][j] == 1:
                line = line + "#"
            else:
                line = line + "."
        output.write(line)
        output.write("\n")

T, r, c = prepareTable()
while True:
    T, finish = alg(T, r, c)
    if finish:
        break
    randomizeTable(T, r, c)
result(T, r, c)