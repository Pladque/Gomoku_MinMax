class MinMax
{
private:
    char AI_character;
    char Opponent_character;
public:
    MinMax(char AI_Char);
    int FindBestMove(int **board, char turn, int depth, bool topLevel = false);
};

MinMax::MinMax(char AI_Char)
{
    AI_character = AI_Char;
    if (AI_Char == 'X')
        Opponent_character = 'O';
    else
        Opponent_character = 'X';

}

int MinMax::FindBestMove(int **board, char turn, int depth,char maximaler,char minimaler,  bool topLevel = false)
{
    vector<vector<bool>> all_moves =  GetAllMoves(board);

    if (depth == 0)
    {
        return EvalBoard(board,  maximaler,  minimaler)
    }

    int [15][15]my_board = board;    //change it to copying later
    int bestscore = -1000;
    vector<vector<int>> chosenMove = {-1,-1};

    if (turn == maximaler)
    {
        for (int i=0; i<15; i++)
        {
            for (int j=0; j<15; j++)
            {
                if(all_moves[i][j] == true)
                {
                    myboard[i][j] = maximaler;
                    temp = indBestMove(myboard,  minimaler,  depth-1, maximaler, minimaler)

                    if(temp>bestscore)
                    {
                        bestscore = temp
                        chosenMove = {i,j}
                    }
                }
            }
        }
    }
    else
    {   
        bestscore = 1000
         for (int i=0; i<15; i++)
        {
            for (int j=0; j<15; j++)
            {
                if(all_moves[i][j] == true)
                {
                    myboard[i][j] = minimaler;
                    temp = indBestMove(myboard,  maximaler,  depth-1, maximaler, minimaler)

                    if(temp<bestscore)
                    {
                        bestscore = temp
                        chosenMove = {i,j}
                    }
                }
            }
        }

    }

    return bestscore
}

char GetWinner(int **board)
{
    for (int i = 0; i<15; i++)
    {
        for (int j = 0; j<15; j++)
        {
            
        }
    }

    return 'D'
}

//return 15x15 board, if value is true, valid move
bool[][] GetAllMoves(int **board)
{
    vector<vector<int>> moves = {
        {false, false, false},
        {false, false, false},
        {false, false, false}
    }
    return moves;
}

int EvalBoard(int **board, char maximaler, char minimaler)
{
    char winner = GetWinner(board);
    if (winner == maximaler)        return 1000;
    else if (winner == minimaler)   return -1000;
    else
    {
        return GetAmountOf_3_OR_2_InRow(board, maximaler, minimaler);
        
    }
    
}

int GetAmountOf_3_OR_2_InRow(int **board, char maximaler, char minimaler) //AI +, player -
{
    return 1;
}
