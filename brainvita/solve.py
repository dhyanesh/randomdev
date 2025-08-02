#!/opt/homebrew/bin/python3

from enum import Enum
import copy
import random
import functools

rows = 7
cols = 7

board_mask = [
  0b0011100,
  0b0011100,
  0b1111111,
  0b1111111,
  0b1111111,
  0b0011100,
  0b0011100,
]

def IsValidIndex(x):
    return x >= 0 and x < rows

class Pos:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def IsValid(self):
        return IsValidIndex(self.x) and IsValidIndex(self.y) and board_mask[self.x]&(1<<self.y) != 0
    def __str__(self):
        return ("(%d,%d)" % (self.x, self.y))

class Direction(Enum):
    UP = 1
    DOWN = 2
    LEFT = 3
    RIGHT = 4

def ReverseDirection(direction):
    if (direction == Direction.UP):
        return Direction.DOWN
    elif (direction == Direction.DOWN):
        return Direction.UP
    elif (direction == Direction.LEFT):
        return Direction.RIGHT
    elif (direction == Direction.RIGHT):
        return Direction.LEFT
    else:
        assert false

class Move:
    def __init__(self, pos, direction):
        self.pos = pos
        self.direction = direction

    def __str__(self):
       return str(self.pos) + str(self.direction)

def ApplyDirection(pos, inc, direction):
    npos = Pos(pos.x, pos.y)
    if (direction == Direction.UP):
        npos.x = pos.x - inc
    elif (direction == Direction.DOWN):
        npos.x = pos.x + inc
    elif (direction == Direction.LEFT):
        npos.y = pos.y - inc
    elif (direction == Direction.RIGHT):
        npos.y = pos.y + inc
    else:
        assert false
    if not npos.IsValid(): return None
    return npos

class Board:
    def __init__(self):
        self.board = board_mask.copy()
        self.Clear(Pos(3, 3))
        assert not self.IsSet(Pos(3, 3))

    def Set(self, pos):
        self.board[pos.x]|=(1<<pos.y)

    def Clear(self, pos):
        self.board[pos.x]&=~(1<<pos.y)

    def IsSet(self, pos):
        return self.board[pos.x]&(1<<pos.y) != 0

    def __str__(self):
      ret = ""
      r = 0
      for row in self.board:
        row_str = ""
        for col in range(0, cols):
          if (1<<col & board_mask[r]):
            row_str += ("X " if (row & 1<<col) else "0 ")
          else:
            row_str += "  "
        ret += row_str + "\n"
        r += 1
      ret += str(self.Count()) + "\n"
      return ret

    def FindMoves(self):
        moves = []
        for row in range(0, rows):
            for col in range(0, cols):
                pos = Pos(row, col)
                if not pos.IsValid(): continue
                if self.IsSet(pos): continue
                for dir in Direction:
                    jumped = ApplyDirection(pos, 1, dir)
                    if jumped is None or not self.IsSet(jumped): continue
                    origin = ApplyDirection(pos, 2, dir)
                    if origin is None or not self.IsSet(origin): continue
                    moves.append(Move(origin, ReverseDirection(dir)))
        return moves

    def ApplyMove(self, move):
        jumped = ApplyDirection(move.pos, 1, move.direction)
        assert jumped!=None and self.IsSet(jumped)
        destination = ApplyDirection(move.pos, 2, move.direction)
        assert destination!=None and not self.IsSet(destination)
        self.Clear(jumped)
        self.Set(destination)
        self.Clear(move.pos)

    def Count(self):
        count = 0
        for row in self.board:
            while row != 0:
                count = count + 1
                row &= (row - 1)
        return count

def RandomSolve(board):
    while True:
        moves = board.FindMoves()
        if len(moves) == 0: break
        board.ApplyMove(random.choice(moves))
        print(board)

@functools.cache
def OptimalSolve(board):
    moves = board.FindMoves()
    min_count = board.Count()
    if min_count == 1:
        print(board)
    for move in moves:
        nb = copy.deepcopy(board)
        nb.ApplyMove(move)
        count = OptimalSolve(nb)
        if count < min_count:
            min_count = count
    return min_count

board = Board()
print(board)

# RandomSolve(board)
print(OptimalSolve(board))
