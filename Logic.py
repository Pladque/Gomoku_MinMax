
def GetWinner(board):
    for x in range(3):
        if board[x][0]== board[x][1]== board[x][2]:
            if board[1][1] != 0: return  board[x][0]
        
        if board[0][x]== board[1][x]== board[2][x]:
            if board[1][1] != 0: return board[2][x]

    if  board[1][1] == board[0][0] == board[2][2] or \
         board[1][1]==board[0][2] == board[2][0]:
        if board[1][1] != 0: return board[1][1]

    return -1

def GetAllMoves(board, player):
    moves = []
    for y, row in enumerate(board):
        for x, field in enumerate(row):
            if field == 0:
                moves.append([x,y])

    return moves

def EvalBoard(board):
    pass

def copy_board( board):
    new_board = []

    for x, row in enumerate(board):
        new_board.append([])
        for field in row:
            new_board[x].append(field)

    return new_board
