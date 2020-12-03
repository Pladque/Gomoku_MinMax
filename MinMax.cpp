#include <vector>
#include <iostream>
#include <bits/stdc++.h>    //min max int values

using namespace std;

int GetAmountOf_4_OR_3_InRow(vector<vector<char>>board, char maximaler, char minimaler, int x_substractor = 0, int y_substractor = 0);
int EvalBoard(vector<vector<char>>board, char maximaler, char minimaler, int x_substractor = 0, int y_substractor = 0);
vector<vector<bool>> GetAllMoves(vector<vector<char>>board, int x_substractor = 0, int y_substractor = 0);
char GetWinner(vector<vector<char>>board,int x_substractor = 0,int y_substractor = 0);

vector<vector<vector<char>>> ALLBOARDS;

class MinMax
{
private:
public:
    char AI_character;
    char Opponent_character;
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

int MinMax::FindBestMove(vector<vector<char>> board, char turn, int depth,int alpha, int beta, char maximaler,char minimaler, int move_x, int move_y,  int x_substractor, int y_substractor) 
{
    if (depth == 0)
        return EvalBoard(board,  maximaler,  minimaler, x_substractor, y_substractor); 

    char winner = GetWinner(board,  x_substractor, y_substractor);
    if (winner!='0')
        return (winner = maximaler) ? INT_MAX : INT_MIN;

    vector<vector<bool>> all_moves =  GetAllMoves(board, x_substractor, y_substractor);
    vector<vector<char>>my_board = board;    //change it to copying later(but is coping already i think)
    int bestscore = (turn == maximaler) ? INT_MIN : INT_MAX;
    my_board[move_x][move_y] = (turn == minimaler) ? maximaler : minimaler;     //not sure if maximaler or minimaler here
    
    ///IDK IF IT IS GOOD???
    for (int i = 0; i< ALLBOARDS.size(); i++)     
    {
        if (ALLBOARDS[i] == my_board)   //mby I can add additional place(char) to the end of my_board, that save its leve
        {                               //so I could find it by levels (how many moves has been done)
            return -7774463;    //code, if FindBestMove return it, function level up shouldnt consider that path
        }
    }
    ALLBOARDS.push_back(my_board);
    ////////////////////////

    
    vector<vector<bool>> all_moves =  GetAllMoves(board, x_substractor, y_substractor);
    int eval;
    // Finding for maximaler
    if (turn == maximaler)
    {
        for (int i=x_substractor; i<=14 - x_substractor; i++)
            for (int j=y_substractor; j<=14 - y_substractor; j++)
                if(all_moves[i][j])
                {
                    eval = FindBestMove(my_board,  minimaler,  depth-1,alpha, beta, maximaler, minimaler,i,j, x_substractor, y_substractor);
                    bestscore = max(eval, bestscore);
                    alpha = max(eval, alpha);
                    if (beta<= alpha)
                        return bestscore;
                }

        return bestscore;    
    }
    // Finding for minimaler
    else
    {
        for (int i=x_substractor; i<=14 - x_substractor; i++)
            for (int j=y_substractor; j<=14 - y_substractor; j++)
                if(all_moves[i][j])
                {
                    eval = FindBestMove(my_board,  minimaler,  depth-1, alpha, beta, maximaler, minimaler,i,j, x_substractor, y_substractor);
                    bestscore = min(eval, bestscore);
                    beta = min(eval, beta);
                    if (beta<= alpha)
                        return bestscore;
                }
    }

        return bestscore;
}

// int x_substractor ,int  y_substractor  I will calculate in python and python will have saved smalles value of it and that smalles values will be sent here
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
        if (str_board[i] == '0'     ||  str_board[i] == 'O' ||  str_board[i] == 'X')
        {
            board[(int)i/15].push_back(str_board[i]);
        }
    }

    vector<vector<bool>> possible_moves = GetAllMoves(board, x_substractor, y_substractor);
    int bestScore = INT_MIN;
    int temp;
    int BestInd = 0;

    for (int i =0; i<15; i++)
    {
        for(int j = 0; j<15; j++)
        {
            if (possible_moves[i][j])
            {
                temp = AI->FindBestMove(board, AI->Opponent_character, depth-1,INT_MIN, INT_MAX ,maximaler, minimaler,  i,  j,  x_substractor ,  y_substractor ) ;
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

char GetWinner(vector<vector<char>>board, int x_substractor, int y_substractor)
{
    for (int i = y_substractor; i<=14 - y_substractor; i++)
    {
        for (int j = x_substractor; j<=14 - x_substractor; j++)
        {
            if(board[i][j]!='0')
            {
                // Checking column
                if(i>=4 && board[i][j]==board[i-1][j] && board[i-1][j]==board[i-2][j]
                    &&  board[i-2][j] == board[i-3][j] && board[i-3][j]==board[i-4][j])
                    {
                        return board[i][j];
                    }
                //checking row
                if(j>=4 && board[i][j]==board[i][j-1] && board[i][j-1]==board[i][j-2]
                    &&  board[i][j-2] == board[i][j-3] && board[i][j-3]==board[i][j-4])
                    {
                        return board[i][j];
                    }
                //checking diagnals from upper left to bottom right
                if(i>=4 && j>=4 && board[i][j]==board[i-1][j-1] && board[i-1][j-1]==board[i-2][j-2]
                    &&  board[i-2][j-2] == board[i-3][j-3] && board[i-3][j-3]==board[i-4][j-4])
                    {
                        return board[i][j];
                    }
                //checking diagnals from upper right to bottom left
                if(i<=10 &&j>=4 &&  board[i][j]==board[i+1][j-1] && board[i+1][j-1]==board[i+2][j-2]
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
vector<vector<bool>> GetAllMoves(vector<vector<char>> board, int x_substractor, int y_substractor) //#DONE WORK
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
int EvalBoard(vector<vector<char>> board , char maximaler, char minimaler, int x_substractor, int y_substractor)
{
    switch(GetWinner(board, x_substractor, y_substractor))
    {
        case 'X': 
            return INT_MAX;
        case 'O': 
            return INT_MIN;
        default:
            return GetAmountOf_4_OR_3_InRow(board, maximaler, minimaler, x_substractor,  y_substractor); 
    }
    
}

int GetAmountOf_4_OR_3_InRow(vector<vector<char>>board, char maximaler, char minimaler, int x_substractor, int y_substractor) //AI +, player -
{
    int score = 0;
    int amount_of_maximaler_temp;
    for (int i = 0; i<=14; i+=1)
    {
        for (int j = 0; j<=14; j+=1)
        {
            amount_of_maximaler_temp = 0;
            if (board[i][j] == maximaler)
            {
                // Checking row
                if (i>=4)
                {
                    if(board[i][j]==board[i-1][j]) 
                    {
                        amount_of_maximaler_temp++;
                    }
                    if(board[i][j]==board[i-2][j]) 
                    {
                        amount_of_maximaler_temp++;
                    }
                    if(board[i][j]==board[i-3][j] ) 
                    {
                        amount_of_maximaler_temp++;
                    }
                    if(board[i][j]==board[i-4][j]) 
                    {
                        amount_of_maximaler_temp++;
                    };

                    if (!(board[i-4][j] == minimaler ||board[i-3][j] == minimaler 
                        ||board[i-2][j] == minimaler ||board[i-1][j] == minimaler))
                        {
                            if (amount_of_maximaler_temp>=3)
                            {
                                score+=2;
                            }
                            else if (amount_of_maximaler_temp==2)
                            {
                                score+=1;
                            }
                        }



                }
                amount_of_maximaler_temp = 0;
                if (j>=4)
                {
                    //checking column
                    if(board[i][j]==board[i][j-1] )
                    {
                        amount_of_maximaler_temp++;
                    }
                    if(board[i][j]==board[i][j-2] )
                    {
                        amount_of_maximaler_temp++;
                    }
                    if(board[i][j]==board[i][j-3] )
                    {
                        amount_of_maximaler_temp++;
                    }
                    if(board[i][j]==board[i][j-4] )
                    {
                        amount_of_maximaler_temp++;
                    }

                    if (!(board[i][j-4] == minimaler ||board[i][j-3] == minimaler 
                        ||board[i][j-2] == minimaler ||board[i][j-1] == minimaler))
                        {
                            if (amount_of_maximaler_temp>=3)
                            {
                                score+=2;
                            }else if (amount_of_maximaler_temp==2)
                            {
                                score+=1;
                            }
                        }


                }
                amount_of_maximaler_temp=0;
                //checking diagnals from bottom left to upper right
                if (j>=4 && i>=4)
                {
                    if(board[i][j]==board[i-1][j-1] )
                        {
                            amount_of_maximaler_temp++;
                        }
                        if(board[i][j]==board[i-2][j-2])
                        {
                            amount_of_maximaler_temp++;
                        }
                        if(board[i][j]==board[i-3][j-3] )
                        {
                            amount_of_maximaler_temp++;
                        }
                        if(board[i][j]==board[i-4][j-4] )
                        {
                            amount_of_maximaler_temp++;
                        };

                        if (!(board[i-4][j-4] == minimaler ||board[i-3][j-3] == minimaler 
                        ||board[i-2][j-2] == minimaler ||board[i-1][j-1] == minimaler))
                        {
                            if (amount_of_maximaler_temp>=3)
                            {
                                score+=2;
                            }else if (amount_of_maximaler_temp==2)
                            {
                                score+=1;
                            }
                        }

                }
                //checking diagnals from bottom left to upper right  
                if (j<=10 && i>=4)
                {
                    if(board[i][j]==board[i-1][j+1] )
                        {
                            amount_of_maximaler_temp++;
                        }
                        if(board[i][j]==board[i-2][j+2] )
                        {
                            amount_of_maximaler_temp++;
                        }
                        if(board[i][j]==board[i-3][j+3])
                        {
                            amount_of_maximaler_temp++;
                        }
                        if(board[i][j]==board[i-4][j+4] )
                        {
                            amount_of_maximaler_temp++;
                        };

                        if (!(board[i-4][j+4] == minimaler ||board[i-3][j+3] == minimaler 
                        ||board[i-2][j+2] == minimaler ||board[i-1][j+1] == minimaler))
                        {
                            if (amount_of_maximaler_temp>=3)
                            {
                                score+=2;
                            }else if (amount_of_maximaler_temp==2)
                            {
                                score+=1;
                            }
                        }

                }
            }else if (board[i][j] == minimaler)
            {
                 // Checking row
                if (i>=4)
                {
                    if(board[i][j]==board[i-1][j] )
                    {
                        amount_of_maximaler_temp++;
                    }
                    if(board[i][j]==board[i-2][j] )
                    {
                        amount_of_maximaler_temp++;
                    }
                    if(board[i][j]==board[i-3][j] )
                    {
                        amount_of_maximaler_temp++;
                    }
                    if(board[i][j]==board[i-4][j] )
                    {
                        amount_of_maximaler_temp++;
                    };

                    if (!(board[i-4][j] == maximaler ||board[i-3][j] == maximaler 
                        ||board[i-2][j] == maximaler ||board[i-1][j] == maximaler))
                        {
                            if (amount_of_maximaler_temp>=3)
                            {
                                score-=2;
                            }else if (amount_of_maximaler_temp==2)
                            {
                                score-=1;
                            }
                        }

                }
                amount_of_maximaler_temp = 0;
                if (j>=4)
                {
                    //checking column
                    if(board[i][j]==board[i][j-1] )
                    {
                        amount_of_maximaler_temp++;
                    }
                    if(board[i][j]==board[i][j-2] )
                    {
                        amount_of_maximaler_temp++;
                    }
                    if(board[i][j]==board[i][j-3] )
                    {
                        amount_of_maximaler_temp++;
                    }
                    if(board[i][j]==board[i][j-4])
                    {
                        amount_of_maximaler_temp++;
                    };

                    if (!(board[i][j-4] == maximaler ||board[i][j-3] == maximaler 
                        ||board[i][j-2] == maximaler ||board[i][j-1] == maximaler))
                        {
                            if (amount_of_maximaler_temp>=3)
                            {
                                score-=2;
                            }else if (amount_of_maximaler_temp==2)
                            {
                                score-=1;
                            }
                        }


                }
                amount_of_maximaler_temp=0;
                //checking diagnals from bottom left to upper right
                if (j>=4 && i>=4)
                {
                    if(board[i][j]==board[i-1][j-1])
                    {
                        amount_of_maximaler_temp++;
                    }
                    if(board[i][j]==board[i-2][j-2] )
                    {
                        amount_of_maximaler_temp++;
                    }
                    if(board[i][j]==board[i-3][j-3])
                    {
                        amount_of_maximaler_temp++;
                    }
                    if(board[i][j]==board[i-4][j-4])
                    {
                        amount_of_maximaler_temp++;
                    };

                        if (!(board[i-4][j-4] == maximaler ||board[i-3][j-3] == maximaler 
                    ||board[i-2][j-2] == maximaler ||board[i-1][j-1] == maximaler))
                    {
                        if (amount_of_maximaler_temp>=3)
                        {
                            score-=2;
                        }else if (amount_of_maximaler_temp==2)
                        {
                            score-=1;
                        }
                    }

                }
                amount_of_maximaler_temp=0;
                //checking diagnals from bottom left to upper right     
                if (j<=10 && i>=4)
                {
                    if(board[i][j]==board[i-1][j+1])
                    {
                        amount_of_maximaler_temp++;
                    }
                    if(board[i][j]==board[i-2][j+2])
                    {
                        amount_of_maximaler_temp++;
                    }
                    if(board[i][j]==board[i-3][j+3])
                    {
                        amount_of_maximaler_temp++;
                    }
                    if(board[i][j]==board[i-4][j+4])
                    {
                        amount_of_maximaler_temp++;
                    };

                        if (!(board[i-4][j+4] == maximaler ||board[i-3][j+3] == maximaler 
                    ||board[i-2][j+2] == maximaler ||board[i-1][j+1] == maximaler))
                    {
                        if (amount_of_maximaler_temp>=3)
                        {
                            score-=2;
                        }else if (amount_of_maximaler_temp==2)
                        {
                            score-=1;
                        }
                    }
                }
            }
        }
    }
    return score;
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
    //board[10][0] = 'X'; //board[10][0] = 'X';
    board[9][0] = 'O';  board[10][4] = 'X';
    board[8][0] = 'O';  board[10][5] = 'X';
    //board[7][0] = 'O';  board[10][6] = 'X';
    board[6][0] = 'O';  board[10][7] = 'X';
    board[5][0] = 'O';  board[10][8] = 'X';
    
    cout<<"SCORE: "<<GetAmountOf_4_OR_3_InRow(board, 'X','O')<<endl;
    cout<<"WINNER: "<<GetWinner(board, 0,0)<<endl;
    
    cout<<endl;

    for (int i = 0; i<15; i++)
    {
        for (int j = 0; j<15; j++)
        {
            if (board[i][j] == 'X')
                cout<<"\033[32m"<<board[i][j]<<" ";
            else if (board[i][j] == 'O')
                cout<<"\033[31m" <<board[i][j]<<" ";
            else
            {
                cout<<"\033[0m"<<board[i][j]<<" ";
            }
            
        }
        cout<<endl;
    }
    

    /*vector<vector<bool>> moves = GetAllMoves(board);

    for (int i = 0; i<15; i++)
    {
        for (int j = 0; j<15; j++)
        {
            cout<<moves[i][j]<<" ";
        }
        cout<<endl;
    }

*/

}
