# coding: utf-8

import string
import itertools
import sys

Turns = 0

# [WKx][WKy][WRx][WRy][BKx][BKy] liczba tu liczba oznacza w którym ruchu ustawienie było rozpatrywane
Board = [[[[[[-1 for x in range(8)] for y in range(8)] for z in range(8)]
           for q in range(8)] for w in range(8)] for e in range(8)]

# Do pamiętania gdzie może się dana figura dostać, by nie przeszukiwać całej tablicy Board
WKBoard = [[False for x in range(8)] for y in range(8)]
WRBoard = [[False for x in range(8)] for y in range(8)]
BKBoard = [[False for x in range(8)] for y in range(8)]


def king_moves(x, y):
    if x-1 >= 0:
        yield (x-1, y)
    if x-1 >= 0 and y-1 >= 0:
        yield (x-1, y-1)
    if x-1 >= 0 and y+1 <= 7:
        yield (x-1, y+1)
    if x+1 <= 7:
        yield (x+1, y)
    if x+1 <= 7 and y-1 >= 0:
        yield (x+1, y-1)
    if x+1 <= 7 and y+1 <= 7:
        yield (x+1, y+1)
    if y-1 >= 0:
        yield (x, y-1)
    if y+1 <= 7:
        yield (x, y+1)


def rook_moves(x, y):
    i = 1
    while True:
        if x-i >= 0:
            yield (x-i, y)
            i += 1
        else:
            break
    i = 1
    while True:
        if x+i <= 7:
            yield (x+i, y)
            i += 1
        else:
            break
    i = 1
    while True:
        if y-i >= 0:
            yield (x, y-i)
            i += 1
        else:
            break
    i = 1
    while True:
        if y+i <= 7:
            yield (x, y+i)
            i += 1
        else:
            break


# Czy czarny król może zbić biały pionek
def is_black_king_too_close(WKx, WKy, WRx, WRy, BKx, BKy) -> bool:
    if abs(WKx-BKx) < 2 and abs(WKy-BKy) < 2:
        return True
    if abs(WRx-BKx) < 2 and abs(WRy-BKy) < 2:
        return True
    return False


def is_check(WKx, WKy, WRx, WRy, BKx, BKy) -> bool:
    if abs(WKx-BKx) < 2 and abs(WKy-BKy) < 2:
        return True
    if BKx == WRx or BKy == WRy:
        return True
    return False


def is_mat(WKx, WKy, WRx, WRy, BKx, BKy) -> bool:
    # Nie ma mata, bo czarny król może zbić białą figure
    if is_black_king_too_close(WKx, WKy, WRx, WRy, BKx, BKy):
        return False

    if not is_check(WKx, WKy, WRx, WRy, BKx, BKy):
        return False
    for x, y in king_moves(BKx, BKy):
        if not is_check(WKx, WKy, WRx, WRy, x, y):
            return False
    return True


def black_turn() -> tuple:
    global Board, Turns, BKBoard
    prev_turn = Turns
    Turns += 1
    to_check = []
    for i in range(8):
        for j in range(8):
            if BKBoard[i][j]:
                to_check.append((i, j))
    for i, j in to_check:
        for x, y in king_moves(i, j):
            for WKx, WKy, WRx, WRy in itertools.product(range(8), repeat=4):
                # Gdy ustawienie przed ruchem nie było możliwe w poprzedniej turze lub było
                # rozpatrzone wcześniej to pomiń, bo chcemy jak najmniejszą ilość ruchów do mata
                if Board[WKx][WKy][WRx][WRy][i][j] != prev_turn:
                    continue
                # Gdy ustawienie po ruchu było kiedyś rozpatrywane lub jest kolizja, to pomiń
                if Board[WKx][WKy][WRx][WRy][x][y] >= 0 or (x == WKx and y == WKy) or (x == WRx and y == WRy) or (WKx == WRx and WKy == WRy):
                    continue
                # Gdy król jest szachowany po ruchu, to pomiń
                if is_check(WKx, WKy, WRx, WRy, x, y):
                    continue
                Board[WKx][WKy][WRx][WRy][x][y] = Turns
                BKBoard[x][y] = True
    return white_turn()


def white_turn() -> tuple:
    global Board, Turns, WKBoard, WRBoard
    prev_turn = Turns
    Turns += 1
    if Turns > 14:
        return (0, 0, 0, 0, 0, 0)
    to_check = []
    for i in range(8):
        for j in range(8):
            if WKBoard[i][j]:
                to_check.append((i, j))
    for i, j in to_check:
        for x, y in king_moves(i, j):
            for BKx, BKy, WRx, WRy in itertools.product(range(8), repeat=4):
                # Gdy ustawienie przed ruchem nie było możliwe w poprzedniej turze lub było
                # rozpatrzone wcześniej to pomiń, bo chcemy jak najmniejszą ilość ruchów do mata
                if Board[i][j][WRx][WRy][BKx][BKy] != prev_turn:
                    continue
                # Gdy ustawienie po ruchu było kiedyś rozpatrywane lub jest kolizja, to pomiń
                if Board[x][y][WRx][WRy][BKx][BKy] >= 0 or (x == BKx and y == BKy) or (x == WRx and y == WRy) or (BKx == WRx and BKy == WRy):
                    continue
                if is_black_king_too_close(x, y, WRx, WRy, BKx, BKy):
                    continue
                if is_mat(x, y, WRx, WRy, BKx, BKy):
                    return (x, y, WRx, WRy, BKx, BKy)
                Board[x][y][WRx][WRy][BKx][BKy] = Turns
                WKBoard[x][y] = True
    to_check = []
    for i in range(8):
        for j in range(8):
            if WRBoard[i][j]:
                to_check.append((i, j))
    for i, j in to_check:
        for x, y in rook_moves(i, j):
            for WKx, WKy, BKx, BKy in itertools.product(range(8), repeat=4):
                # Gdy ustawienie przed ruchem nie było możliwe w poprzedniej turze lub było
                # rozpatrzone wcześniej to pomiń, bo chcemy jak najmniejszą ilość ruchów do mata
                if Board[WKx][WKy][i][j][BKx][BKy] != prev_turn:
                    continue
                # Gdy ustawienie po ruchu było kiedyś rozpatrywane lub jest kolizja, to pomiń
                if Board[WKx][WKy][x][y][BKx][BKy] >= 0 or (x == BKx and y == BKy) or (x == WKx and y == WKy) or (BKx == WKx and BKy == WKy):
                    continue
                if is_black_king_too_close(WKx, WKy, x, y, BKx, BKy):
                    continue
                if is_mat(WKx, WKy, x, y, BKx, BKy):
                    return (WKx, WKy, x, y, BKx, BKy)
                Board[WKx][WKy][x][y][BKx][BKy] = Turns
                WRBoard[x][y] = True
    return black_turn()


def print_board(WKx, WKy, WRx, WRy, BKx, BKy, out_list, color):
    global Turns
    out_list[Turns] = ""
    out_list[Turns] += "Turn " + str(Turns) + " " + color + "\n\n"
    out_list[Turns] += "  "
    for z in range(8):
        out_list[Turns] += list(string.ascii_lowercase)[z] + "  "
    out_list[Turns] += "\n"
    for x in range(8):
        out_list[Turns] += str(x+1) + " "
        for y in range(8):
            if WKx == y and WKy == x:
                out_list[Turns] += "WK "
            elif WRx == y and WRy == x:
                out_list[Turns] += "WR "
            elif BKx == y and BKy == x:
                out_list[Turns] += "BK "
            else:
                out_list[Turns] += "** "
        out_list[Turns] += "\n"
    out_list[Turns] += "\n"
    Turns -= 1
    if Turns < 0:
        for out_board in out_list:
            print(out_board)
        return
    if color == "black":
        for BKx2, BKy2 in king_moves(BKx, BKy):
            if Board[WKx][WKy][WRx][WRy][BKx2][BKy2] == Turns:
                print_board(WKx, WKy, WRx, WRy, BKx2, BKy2, out_list, "white")
                return
    else:
        for WKx2, WKy2 in king_moves(WKx, WKy):
            if Board[WKx2][WKy2][WRx][WRy][BKx][BKy] == Turns:
                print_board(WKx2, WKy2, WRx, WRy, BKx, BKy, out_list, "black")
                return
        for WRx2, WRy2 in rook_moves(WRx, WRy):
            if Board[WKx][WKy][WRx2][WRy2][BKx][BKy] == Turns:
                print_board(WKx, WKy, WRx2, WRy2, BKx, BKy, out_list, "black")
                return


with open('zad1_input.txt', 'r',  encoding='utf-8') as r:
    with open('zad1_output.txt', 'w',  encoding='utf-8') as w:
        for line in r:
            turn, WKpos, WRpos, BKpos = line.split(" ")
            WKx = ord(WKpos[0]) - 97
            WKy = int(WKpos[1]) - 1
            WRx = ord(WRpos[0]) - 97
            WRy = int(WRpos[1]) - 1
            BKx = ord(BKpos[0]) - 97
            BKy = int(BKpos[1]) - 1

            WKBoard[WKx][WKy] = True
            WRBoard[WRx][WRy] = True
            BKBoard[BKx][BKy] = True
            Board[WKx][WKy][WRx][WRy][BKx][BKy] = 0

            if len(sys.argv) == 2 and sys.argv[1] == "debug":
                if is_mat(WKx, WKy, WRx, WRy, BKx, BKy):
                    print("Szach od razu")
            else:
                if is_mat(WKx, WKy, WRx, WRy, BKx, BKy):
                    w.write('0\n')

            if turn == 'black':
                WKx, WKy, WRx, WRy, BKx, BKy = black_turn()
            else:
                WKx, WKy, WRx, WRy, BKx, BKy = white_turn()

            if len(sys.argv) == 2 and sys.argv[1] == "debug":
                print("WYNIK = ", Turns)
                print_board(WKx, WKy, WRx, WRy, BKx, BKy, [
                            "" for x in range(Turns + 1)], "white")
            else:
                w.write((str(Turns)) + "\n")

            for q, w, e, r, t, y in itertools.product(range(8), repeat=6):
                Board[q][w][e][r][t][y] = -1
            for x, y in itertools.product(range(8), repeat=2):
                WKBoard[x][y] = False
                WRBoard[x][y] = False
                BKBoard[x][y] = False
            Turns = 0
            
