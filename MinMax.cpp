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
    char winner = GetWinner(board);
    if (winner!='0')
    {
        if (winner = maximaler)
            return 9999999;
        else return -99999999;
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


int GetBestMove(string str_board, char turn, int depth,char maximaler,char minimaler)   //function that i will call from python
{
    MinMax* AI = new MinMax(maximaler);
    vector<vector<char>> board;
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
                temp = AI->FindBestMove(board, turn, depth-1, maximaler, minimaler);
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

char GetWinner(vector<vector<char>>board)
{
    for (int i = 4; i<=14; i++)
    {
        for (int j = 4; j<=14; j++)
        {
            // Checking row
            if(board[i][j]==board[i-1][j] && board[i-1][j]==board[i-2][j]
                &&  board[i-2][j] == board[i-3][j] && board[i-3][j]==board[i-4][j]
                && ((i+1 <=14 && board[i][j]!=board[i+1][j] )|| (i-5>=0 && board[i-5][j]!=board[i-4][j])))
                {
                    return board[i][j];
                }
            //checking column
            if(board[i][j]==board[i][j-1] && board[i][j-1]==board[i][j-2]
                &&  board[i][j-2] == board[i][j-3] && board[i][j-3]==board[i][j-4]
                && ((j+1 <=14 && board[i][j]!=board[i][j+1] )|| (j-5>=0 && board[i][j-5]!=board[i][j-4])))
                {
                    return board[i][j];
                }
            //checking diagnals from bottom left to upper right
            //checking diagnals from bottom right to upper left

        }
    }

    return '0';
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
        int score = GetAmountOf_4_OR_3_InRow(board, maximaler, minimaler); 
        return score; 
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
                || (i+1<14 && board[14][j]=='0'))
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
