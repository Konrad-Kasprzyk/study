# coding: utf-8
import copy

class BoxLocation:
    def __init__(self, board, box_locations, X, Y):
        self.board = board
        self.box_locations = box_locations
        self.X = X
        self.Y = Y
        self.no_moves = False
        self.no_box_moves = False
        self.longes_move_list = 1
        for x in range(X):
            for y in range(Y):
                if len(board[x][y]) > self.longes_move_list:
                    self.longes_move_list = len(board[x][y])

    def move(self, x, y):
        change = False
        if len(self.board[x+1][y]) == 1 and self.board[x+1][y] != 'W' and self.board[x+1][y] != 'B' and self.board[x+1][y] != '*':
                if self.board[x+1][y] == 'G':
                    self.board[x+1][y] = '+' + self.board[x][y][1:] + 'U'
                else:
                    self.board[x+1][y] = '.' + self.board[x][y][1:] + 'U'
                change = True
        if len(self.board[x-1][y]) == 1 and self.board[x-1][y] != 'W' and self.board[x-1][y] != 'B' and self.board[x-1][y] != '*':
                if self.board[x-1][y] == 'G':
                    self.board[x-1][y] = '+' + self.board[x][y][1:] + 'D'
                else:
                    self.board[x-1][y] = '.' + self.board[x][y][1:] + 'D'
                change = True
        if len(self.board[x][y+1]) == 1 and self.board[x][y+1] != 'W' and self.board[x][y+1] != 'B' and self.board[x][y+1] != '*':
                if self.board[x][y+1] == 'G':
                    self.board[x][y+1] = '+' + self.board[x][y][1:] + 'R'
                else:
                    self.board[x][y+1] = '.' + self.board[x][y][1:] + 'R'
                change = True
        if len(self.board[x][y-1]) == 1 and self.board[x][y-1] != 'W' and self.board[x][y-1] != 'B' and self.board[x][y-1] != '*':
                if self.board[x][y-1] == 'G':
                    self.board[x][y-1] = '+' + self.board[x][y][1:] + 'L'
                else:
                    self.board[x][y-1] = '.' + self.board[x][y][1:] + 'L'
                change = True
        return change

        # add new moves to current board without moving boxes
    def newMoves(self):
        if self.no_moves:
            return
        no_moves = True
        for x in range(self.X):
            for y in range(self.Y):
                if ( len(self.board[x][y]) > 1 and len(self.board[x][y]) == self.longes_move_list ) or self.board[x][y] == 'K' or self.board[x][y] == '+':
                    if self.move(x, y):
                        no_moves = False
        self.longes_move_list += 1
        if no_moves:
            self.no_moves = True


    
    # returns list of (new box location, old box location, player moves, box letter)
    def boxMoves(self, x, y):
        result = []
        if (x+1, y) in self.box_locations:
            if self.board[x+2][y] != 'W' and self.board[x+2][y] != 'B' and self.board[x+2][y] != '*':
                if self.board[x+1][y] == '*':
                    player_moves = '+' + self.board[x][y] + 'U'
                else:
                    player_moves = '.' + self.board[x][y] + 'U'
                if self.board[x+2][y] == 'G':
                    box_letter = '*'
                else:
                    box_letter = 'B'
                result.append( ((x+1,y), (x+2,y), player_moves, box_letter) )
        if (x-1, y) in self.box_locations:
            if self.board[x-2][y] != 'W' and self.board[x-2][y] != 'B' and self.board[x-2][y] != '*':
                if self.board[x-1][y] == '*':
                    player_moves = '+' + self.board[x][y] + 'D'
                else:
                    player_moves = '.' + self.board[x][y] + 'D'
                if self.board[x-2][y] == 'G':
                    box_letter = '*'
                else:
                    box_letter = 'B'
                result.append( ((x-1,y), (x-2,y), player_moves, box_letter) )
        if (x, y+1) in self.box_locations:
            if self.board[x][y+2] != 'W' and self.board[x][y+2] != 'B' and self.board[x][y+2] != '*':
                if self.board[x][y+1] == '*':
                    player_moves = '+' + self.board[x][y] + 'R'
                else:
                    player_moves = '.' + self.board[x][y] + 'R'
                if self.board[x][y+2] == 'G':
                    box_letter = '*'
                else:
                    box_letter = 'B'
                result.append( ((x,y+1), (x,y+2), player_moves, box_letter) )
        if (x, y-1) in self.box_locations:
            if self.board[x][y-2] != 'W' and self.board[x][y-2] != 'B' and self.board[x][y-2] != '*':
                if self.board[x][y-1] == '*':
                    player_moves = '+' + self.board[x][y] + 'L'
                else:
                    player_moves = '.' + self.board[x][y] + 'L'
                if self.board[x][y-2] == 'G':
                    box_letter = '*'
                else:
                    box_letter = 'B'
                result.append( ((x,y-1), (x,y-2), player_moves, box_letter) )
        return result

        # return (new box locations, old box location, new box location, player moves, box letter) -> moves to boxes
    def newBoxLocations(self):
        if self.no_box_moves:
            return []
        result = []
        for x in range(self.X):
            for y in range(self.Y):
                if len(self.board[x][y]) > 1 or self.board[x][y] == 'K' or self.board[x][y] == '+':
                    res_fun_list = self.boxMoves(x, y)
                    for res_fun in res_fun_list:
                        old_box_location, new_box_location, player_moves, box_letter = res_fun
                        new_box_locations = copy.deepcopy(self.box_locations)
                        new_box_locations.remove(old_box_location)
                        new_box_locations.add(new_box_location)
                        result.append( (new_box_locations, old_box_location, new_box_location, player_moves, box_letter) )
        if not result and self.no_moves:
            self.no_box_moves = True
        return result

class GameMaster:
    def __init__(self, board, X, Y):
        self.boxLocations = []
        self.X = X
        self.Y = Y
        self.first_moves(board)

    def first_moves(self, board):
        box_locations = set()
        for x in range(self.X):
            for y in range(self.Y):
                if board[x][y] == 'B' or board[x][y] == '*':
                    box_locations.add( (x,y) )
        boxLocation = BoxLocation(board, box_locations, self.X, self.Y)
        self.boxLocations.append(boxLocation)

    
    def addBoxLocation(self, board, boxLocations):
        self.boxLocations.append(BoxLocation(board, boxLocations, self.X, self.Y))


def finished(board, X, Y):
        for x in range(X):
            for y in range(Y):
                if board[x][y] == '+' or board[x][y] == 'G':
                    return False
        return True


def Alg(board, X, Y):
    gameMaster = GameMaster(board, X, Y)
    while(True):
        boards_to_add = []
        box_locations_to_add = []
        for boxLocation in gameMaster.boxLocations:
            newBoxLocations = boxLocation.newBoxLocations()
            for newBoxLocation in newBoxLocations:
                new_box_locations, old_box_location, new_box_location, player_moves, box_letter = newBoxLocation
                # if we had this box arrangemet earlier we don't make new BoxLocation
                if new_box_locations in box_locations_to_add:
                    continue
                boxLocation_already_made = False
                for boxLocation2 in gameMaster.boxLocations:
                    print(boxLocation2.box_locations)
                    if new_box_locations == boxLocation2.box_locations:
                        boxLocation_already_made = True
                        break
                print()
                if boxLocation_already_made:
                    continue
                
                board = copy.deepcopy(boxLocation.board)
                # cleaning moves from prevoius board
                for x in range(X):
                    for y in range(Y):
                        if len(board[x][y]) > 1:
                            board[x][y] = board[x][y][:1]
                            if board[x][y] == '+':
                                board[x][y] = 'G'
                x, y = old_box_location
                board[x][y] = player_moves
                x, y = new_box_location
                board[x][y] = box_letter
                if finished(board, X, Y):
                    return player_moves[1:]
                boards_to_add.append(board)
                box_locations_to_add.append(new_box_locations)
            
        # print(gameMaster.boxLocations[len(gameMaster.boxLocations) - 1].board)
        # print()
        # print(len(gameMaster.boxLocations))
        for boxLocation in gameMaster.boxLocations:
            boxLocation.newMoves()

        for i in range(len(boards_to_add)):
            gameMaster.addBoxLocation(boards_to_add[i], box_locations_to_add[i])


def Main():
    board = []
    file = open("zad_input.txt", encoding='utf-8')
    for line in file:
        if line[len(line) - 1] == '\n':
            line = line[:-1]
        board.append(line)
    X = len(board)
    Y = len(board[0])
    board2 = []
    for x in range(X):
        l = []
        for y in range(Y):
            l.append(board[x][y])
        board2.append(l)
    print(Alg(board2, X, Y))


Main()