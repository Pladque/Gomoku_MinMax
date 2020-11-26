from Logic import GetWinner
from pygame import time
from AI import AI
from termcolor import colored

clock = time.Clock()
def showBoard():
    for row in BOARD:
        print(row)

BOARD = [
[0 ,0, 0],
[0 ,0, 0],
[0 ,0, 0],
]
turn = 'O'
depth = 9

opponent = AI(AI_character = 'X')
player_char = 'O'

winner = '-1'
while winner == '-1':
    if turn == opponent.AI_character: 
        move = opponent.FindBestMove(BOARD, opponent.AI_character, depth, True)
        BOARD[move[1]][move[0]] = opponent.AI_character
        
        turn = player_char
        depth -=1
    else:
        showBoard()
        
        player_move_x = int (input('X: '))
        player_move_y = int(input('Y: '))

        BOARD[player_move_y][player_move_x] = player_char
        turn = opponent.AI_character
        depth -=1

    winner = GetWinner(BOARD)
    clock.tick(1)

showBoard()

print(colored('WINNER: ', 'green'), end = '')
print(colored(winner, 'green'))



