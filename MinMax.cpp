#include <vector>
#include <iostream>
using namespace std;

int GetAmountOf_3_OR_2_InRow(vector<vector<char>>board, char maximaler, char minimaler);
int EvalBoard(vector<vector<char>>board, char maximaler, char minimaler);
vector<vector<bool>> GetAllMoves(vector<vector<char>>board);


class MinMax
{
private:
    char AI_character;
    char Opponent_character;
public:
    MinMax(char AI_Char);
    int FindBestMove(vector<vector<char>>board, char turn, int depth,char maximaler,char minimaler);
};

MinMax::MinMax(char AI_Char)
{
    AI_character = AI_Char;
    if (AI_Char == 'X')
        Opponent_character = 'O';
    else
        Opponent_character = 'X';

}

int MinMax::FindBestMove(vector<vector<char>>board, char turn, int depth,char maximaler,char minimaler)
{
    vector<vector<bool>> all_moves =  GetAllMoves(board);

    if (depth == 0)
    {
        int board_score = EvalBoard(board,  maximaler,  minimaler); 
        return board_score;
    }

    vector<vector<char>>my_board = board;    //change it to copying later
    int bestscore = -1000;
    vector<int> chosenMove = {-1,-1};

    if (turn == maximaler)
    {
        int temp = 0;
        for (int i=0; i<15; i++)
        {
            for (int j=0; j<15; j++)
            {
                if(all_moves[i][j] == true)
                {
                    my_board[i][j] = maximaler;
                    temp = FindBestMove(my_board,  minimaler,  depth-1, maximaler, minimaler);

                    if(temp>bestscore)
                    {
                        bestscore = temp;
                        chosenMove = {i,j};
                    }
                }
            }
        }
    }
    else
    {   
        int temp = 0;
        bestscore = 1000;
        for (int i=0; i<15; i++)
        {
            for (int j=0; j<15; j++)
            {
                if(all_moves[i][j] == true)
                {
                    my_board[i][j] = minimaler;
                    temp = FindBestMove(my_board,  maximaler,  depth-1, maximaler, minimaler);

                    if(temp<bestscore)
                    {
                        bestscore = temp;
                        chosenMove = {i,j};
                    }
                }
            }
        }

    }

    return bestscore;
}


int GetBestMove()   //function that i will call from python
//it should work like FirstLevel in min max and it will return best move
//as int. remember to create a MinMax Object here
{
    MinMax* AI = new MinMax('X');
    return 0;
}

char GetWinner(vector<vector<char>>board)
{
    for (int i = 0; i<15; i++)
    {
        for (int j = 0; j<15; j++)
        {
            
        }
    }

    return 'D';
}

//return 15x15 board, if value is true, valid move
vector<vector<bool>> GetAllMoves(vector<vector<char>>board) //#DONE WORK
{
    vector<vector<bool>> moves;
    for (int i = 0; i<15; i++)
    {
        vector<bool> empty_vec;
        moves.push_back(empty_vec);
        for (int j = 0; j<15; j++)
        {
            if (board[i][j] == '0')
                moves[i].push_back(true);
            else 
                moves[i].push_back(false);
        }
    }

    return moves;
}

int EvalBoard(vector<vector<char>> board , char maximaler, char minimaler)
{
    char winner = GetWinner(board);
    if (winner == maximaler)        return 1000;
    else if (winner == minimaler)   return -1000;
    else
    {
        int score = GetAmountOf_3_OR_2_InRow(board, maximaler, minimaler); 
        return score;
        
    }
    
}

int GetAmountOf_3_OR_2_InRow(vector<vector<char>>board, char maximaler, char minimaler) //AI +, player -
{
    return 1;
}


int main()
{
    vector<vector<char>> board;

    for (int i = 0; i<15; i++)
    {
        vector<char> empty_vec;
        board.push_back(empty_vec);
        for (int j = 0; j<15; j++)
        {
            board[i].push_back('0');
        }
    }

    board[1][1] = 'X';

    for (int i = 0; i<15; i++)
    {
        for (int j = 0; j<15; j++)
        {
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
    
    cout<<endl;

    vector<vector<bool>> moves = GetAllMoves(board);

    for (int i = 0; i<15; i++)
    {
        for (int j = 0; j<15; j++)
        {
            cout<<moves[i][j]<<" ";
        }
        cout<<endl;
    }



}
