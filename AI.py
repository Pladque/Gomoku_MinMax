from Logic import *
class AI:
    
    def __init__(self, board, AI_character = 'O'):
        self.board = board
        self.AI_character = AI_character

    

    def FindBestMove(self, board, turn, depth):
        if depth ==0:
            return EvalBoard(board)
        
        my_board = copy_board(board)
        best_score = -1000

        if turn =='X':
            for move in GetAllMoves(my_board):
                my_board[move[0]][move[1]] = 'X'
                temp = self.FindBestMove(my_board, 'O', depth-1 )
                my_board[move[0]][move[1]] = 0

                if temp > best_score:
                    best_score = temp
        else:
            pass

