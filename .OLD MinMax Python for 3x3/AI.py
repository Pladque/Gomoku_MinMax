from Logic import *
class AI:
    
    def __init__(self, AI_character = 'O'):
        self.AI_character = AI_character
        if AI_character == 'X':
            self.player_char = 'O'
        else:
            self.player_char = 'X'

    

    def FindBestMove(self, board, turn, depth, topLevel = False):
        all_moves = GetAllMoves(board)

        if depth == 0 or all_moves is []:
            return EvalBoard(board, self.AI_character, self.player_char)
        
        winner = GetWinner(board)
        if winner == self.AI_character:
            return 10
        elif winner == self.player_char:
            return -10

        
        my_board = copy_board(board)
        best_score = -1000
        chosen_move = 0

        if topLevel: print(all_moves)

        if turn == self.AI_character:
            for move in all_moves:
                my_board[move[1]][move[0]] =  self.AI_character
                temp = self.FindBestMove(my_board, self.player_char, depth-1 )
                my_board[move[1]][move[0]] = 0

                if temp > best_score:
                    best_score = temp
                    chosen_move = [move[0],move[1]]
        else:
            best_score = 1000
            for move in all_moves:
                my_board[move[1]][move[0]] = self.player_char
                temp = self.FindBestMove(my_board, self.AI_character, depth-1 )
                my_board[move[1]][move[0]] = 0

                if temp < best_score:
                    best_score = temp
                    chosen_move = (move[0],move[1])
        
        if topLevel is False: return best_score

        if topLevel: print(best_score)
        return chosen_move