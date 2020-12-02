#include <vector>
#include <iostream>
using namespace std;

int GetAmountOf_3_OR_2_InRow(vector<vector<char>>board, char maximaler, char minimaler);
int EvalBoard(vector<vector<char>>board, char maximaler, char minimaler, int x_substractor = 0, int y_substractor = 0);
vector<vector<bool>> GetAllMoves(vector<vector<char>>board);


class MinMax
{
private:
    char AI_character;
    char Opponent_character;
public:
    MinMax(char AI_Char);
    int FindBestMove(vector<vector<char>>board, char turn, int depth,int alpha, int beta,char maximaler,char minimaler, int move_x, int move_y,  int x_substractor = 0, int y_substractor = 0);
};

MinMax::MinMax(char AI_Char)
{
    AI_character = AI_Char;
    if (AI_Char == 'X')
        Opponent_character = 'O';
    else
        Opponent_character = 'X';

}

int MinMax::FindBestMove(vector<vector<char>> board, char turn, int depth,int alpha, int beta, char maximaler,char minimaler, int move_x, int move_y,  int x_substractor = 0, int y_substractor = 0) 
{
    if (depth == 0)
        return EvalBoard(board,  maximaler,  minimaler, x_substractor, y_substractor); 

    char winner = GetWinner(board,  x_substractor, y_substractor);
    if (winner!='0')
        return (winner = maximaler) ? 9999999 : -99999999;

    vector<vector<bool>> all_moves =  GetAllMoves(board);
    vector<vector<char>>my_board = board;    //change it to copying later(but is coping alreadi i think)
    int bestscore = (turn == maximaler) ? -1000 : 1000;
    my_board[move_x][move_y] = (turn == minimaler) ? maximaler : minimaler;     //not sure if maximaler or minimaler here
    
    int eval;
    // Finding for maximaler
    if (turn == maximaler)
        for (int i=0; i<15 - x_substractor; i++)
            for (int j=0; j<15 - y_substractor; j++)
                if(all_moves[i][j])
                {
                    eval = FindBestMove(my_board,  minimaler,  depth-1,alpha, beta, maximaler, minimaler,i,j, x_substractor, y_substractor);
                    bestscore = max(eval, bestscore);
                    alpha = max(eval, alpha)
                    if (beta<= alpha)
                        return bestscore;
                }

        return bestscore;    
    // Finding for minimaler
    else
        for (int i=0; i<15 - x_substractor; i++)
            for (int j=0; j<15 - y_substractor; j++)
                if(all_moves[i][j])
                {
                    eval = FindBestMove(my_board,  minimaler,  depth-1, alpha, beta, maximaler, minimaler,i,j, x_substractor, y_substractor);
                    bestscore = min(eval, bestscore);
                    beta = min(eval, beta)
                    if (beta<= alpha)
                        return bestscore;
                }

        return bestscore;
}

// int x_substractor ,int  y_substractor  I will calculate in python and send it here and it will replace old  x_substractor y_substractor if there are < then new ones
int GetBestMove(string str_board, char turn, int depth,char maximaler,char minimaler,  int x_substractor ,int  y_substractor  )    //function that i will call from python
{
    MinMax* AI = new MinMax(maximaler);
    vector<vector<char>> board;
    //converting str 15x15 board to vectors of vector  of chars
    for (int i =0; i<str_board.length(); i++)
    {
        if (i%15==0) 
        {
            vector<char> empty_vec;
            board.push_back(empty_vec);
        }
        if (str_board[i] == '0')
        {
            board[(int)i/15].push_back('0');
        }
    }

    vector<vector<bool>> possible_moves = GetAllMoves(board);
    int bestScore = -99999;
    int temp;
    int BestInd = 0;

    for (int i =0; i<15; i++)
    {
        for(int j = 0; j<15; j++)
        {
            if (possible_moves[i][j])
            {
                temp = AI->FindBestMove(board, AI->Opponent_character, depth-1,-99999999999, 9999999999 maximaler, minimaler,  i,  j,  x_substractor ,  y_substractor ) 
                if (temp > bestScore)
                {
                    bestScore = temp;
                    BestInd= j*15 + i;
                }
            }
        }
    }
    return BestInd;
}

char GetWinner(vector<vector<char>>board, int x_substractor = 0, int y_substractor = 0)
{
    for (int i = 4; i<=14; i++)
    {
        for (int j = 4; j<=14; j++)
        {
            if(board[i][j]!='0')
            {
                // Checking row
                if(board[i][j]==board[i-1][j] && board[i-1][j]==board[i-2][j]
                    &&  board[i-2][j] == board[i-3][j] && board[i-3][j]==board[i-4][j])
                    {
                        return board[i][j];
                    }
                //checking column
                if(board[i][j]==board[i][j-1] && board[i][j-1]==board[i][j-2]
                    &&  board[i][j-2] == board[i][j-3] && board[i][j-3]==board[i][j-4])
                    {
                        return board[i][j];
                    }
                //checking diagnals from upper right to bottom left
                if(board[i][j]==board[i-1][j-1] && board[i-1][j-1]==board[i-2][j-2]
                    &&  board[i-2][j-2] == board[i-3][j-3] && board[i-3][j-3]==board[i-4][j-4])
                    {
                        return board[i][j];
                    }
                //checking diagnals from bottom right to upper left
                if(x<=10 && board[i][j]==board[i+1][j-1] && board[i+1][j-1]==board[i+2][j-2]
                    &&  board[i+2][j-2] == board[i+3][j-3] && board[i+3][j-3]==board[i+4][j-4])
                    {
                        return board[i][j];
                    }
            }
        }
    }

    return '0';
}

//return 15x15 board, if value is true, valid move
vector<vector<bool>> GetAllMoves(vector<vector<char>> board, int x_substractor = 0, int y_substractor = 0) //#DONE WORK
{
    vector<vector<bool>> moves;
    for (int i = 0; i<15 - x_substractor; i++)
    {
        vector<bool> empty_vec;
        moves.push_back(empty_vec);
        for (int j = 0; j<15 - y_substractor; j++)
        {
            if (board[i][j] == '0')
                moves[i].push_back(true);
            else 
                moves[i].push_back(false);
        }
    }

    return moves;
}

//I need winner seperaty!!!
int EvalBoard(vector<vector<char>> board , char maximaler, char minimaler, int x_substractor = 0, int y_substractor = 0)
{
    //but mby I can it do better
    char winner = GetWinner(board, x_substractor, y_substractor);
    if (winner == maximaler)        return 1000;
    else if (winner == minimaler)   return -1000;
    else
    {
        //int score = 
        return GetAmountOf_4_OR_3_InRow(board, maximaler, minimaler); 
    }
    
}

int GetAmountOf_4_OR_3_InRow(vector<vector<char>>board, char maximaler, char minimaler) //AI +, player -
{
    int score = 0;
     for (int i = 3; i<=14; i++)
    {
        for (int j = 3; j<=14; j++)
        {
            if (board[i][j] != '0')
            {
            // Checking row
            if(board[i][j]==board[i-1][j] && board[i-1][j]==board[i-2][j]
                &&  board[i-2][j] == board[i-3][j] && (i-4>=0 && board[i-4][j]=='0')
                || (i+1<14 && board[i+1][j]=='0'))
                {
                    if( board[i][j] == maximaler )
                    {
                        score+=2;
                    }
                    else
                    {
                        score -=2;
                    }
                    
                }
            //checking column
            if(board[i][j]==board[i][j-1] && board[i][j-1]==board[i][j-2]
                &&  board[i][j-2] == board[i][j-2] && (j-4>=0 && board[i][j-4]=='0')
                || (j+1<14 && board[i][j+1]=='0'))
                {
                    if( board[i][j] == maximaler )
                    {
                        score+=2;
                    }
                    else
                    {
                        score -=2;
                    }
                    
                }
            //checking diagnals from bottom left to upper right
            //checking diagnals from bottom right to upper left     
            }
            

        }
    }
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
    board[2][2] = 'X';
    board[3][3] = 'X';
    board[4][4] = 'X';
    board[5][5] = 'X';
    //cout<<GetWinner(board, 0,0)<<endl;

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
