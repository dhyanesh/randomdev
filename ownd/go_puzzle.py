# This puzzle involves setting stones on variously sized square Go boards so
# that the straight-line distances between the stones are all different. For
# each board, you use the same number of stones as the side length (for
# example, on a 3x3 board, you use three stones). On the 3x3 board, it's pretty
# easy to put three stones down so that the distance of a line linking each
# stone—including diagonals, not just on the lines of the board—is different.
# To head off the inevitable edge case questions, we're assuming that the
# distances are measured from the exact points where the Go board lines
# intersect.
#
# For a 7x7 board, there is only one solution (again, this doesn't include
# rotation and reflection). And that brings us to our nerd-snipe of the day: can
# you find the unique solution for placing seven stones on a 7x7 board such that
# no linear distances between stones are the same?

import math

class Point:
  def __init__(self, x, y):
    self.x = x
    self.y = y

  def __str__(self):
    return "(%d, %d)" % (self.x, self.y)

  def __repr__(self):
    return "(%d, %d)" % (self.x, self.y)

  def __eq__(self, other):
    return self.x == other.x and self.y == other.y

  def __hash__(self):
    return hash((self.x, self.y))

def sqrdist(a, b):
    return (a.x - b.x)**2 + (a.y - b.y) ** 2

def dist(a, b):
    return math.sqrt(sqrdist(a,b))

# a = Point(1, 0)
# b = Point(2, 0)
# 
# x = Point(0,0)
# y = Point(3,4)
# 
# print(dist(a,b))
# print(dist(x,y))

def maybeIsNewPoint(xy, points, distances):
    newDistances = {}
    for p in points:
        dist = sqrdist(xy, p)
        if dist in distances.keys():
            return False, {}
        if dist in newDistances.keys():
            return False, {}
        newDistances[dist] = True

    return True, newDistances

def printBoard(board):
    n = len(board)
    for y in range(n - 1, -1, -1):
        printstr = ""
        for x in range(0, n):
            printstr += str(board[x][y]) + " "
        print(printstr)
    print("")

def solve(lx, ly, board, placed, points, distances):
    n = len(board)
    # if placed == n - 1 and Point(0,0) in points.keys() and Point(1,0) in points.keys() and Point(2,1) in points.keys():
    #     print(placed)
    #     printBoard(board)
    if placed == n:
        return True

    for x in range(lx, n):
        for y in range(0, n):
            if board[x][y] == 1:
                continue
            xy = Point(x,y)
            (isNew, newDistances) = maybeIsNewPoint(xy, points, distances)
            if isNew:
                # print("Before")
                # print(points)
                # print(distances)
                passDown = distances.copy()
                passDown.update(newDistances)
                newPoints = points.copy()
                newPoints[xy] = True
                # printBoard(board)
                board[x][y] = 1
                # printBoard(board)
                if solve(x, y, board, placed + 1, newPoints, passDown):
                    return True
                board[x][y] = 0

                # print("After")
                # print(points)
                # print(distances)

    return False

N = 7
board = [[0 for i in range(N)] for j in range(N)]

if solve(0, 0, board, 0, {}, {}):
    printBoard(board)
else:
    print("No solution.")

