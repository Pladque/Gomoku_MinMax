from Logic import GetWinner
from pygame import time
from AI import AI

clock = time.Clock()

def showBoard():
    for row in BOARD:
        print(row)

BOARD = [
[0 ,0, 0],
[0 ,0, 0],
[0 ,0, 0],
]

opponent = AI(BOARD)


while GetWinner(BOARD) == -1:
    clock.tick(30)
    #showBoard()


