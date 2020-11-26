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

int MinMax::FindBestMove(int **board, char turn, int depth, bool topLevel = false)
{
    int **all_moves =  GetAllMoves(board);

    if (depth == 0 or all_moves)

    return 1;
}

int GetWinner(int **board)
{
    for (int i = 0; i<15; i++)
    {
        for (int j = 0; j<15; j++)
        {
            
        }
    }
}

//return 15x15 board, if value is true, valid move
bool[][] GetAllMoves(int **board)
{
    bool **ret[1][1] = {{false}};
    return **ret;
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
