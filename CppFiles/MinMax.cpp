#include <vector>
#include <iostream>
#include <map>					//hashmaps
#include <chrono>				//clock
#include <thread>
#include <fstream>
#include <cstdlib>
//#include <bits/stdc++.h>		//min max int values

using namespace std;

int ScoreBoard(char board[15][15], char& maximaler, char& minimaler);
int EvalBoard(char board[15][15], char& maximaler, char& minimaler);
void GetAllMoves(char board[15][15], bool moves[15][15]);
char GetWinner(char board[15][15]);
int FindBestMove(char board[15][15], char turn, int depth, int alpha, int beta, char& maximaler, char& minimaler, short& move_x, short& move_y);

class MinMax
{
private:
public:
	char AI_character;
	char Opponent_character;
	MinMax(char AI_Char);
};

MinMax::MinMax(char AI_Char)
{
	AI_character = AI_Char;
	if (AI_Char == 'X')
		Opponent_character = 'O';
	else
		Opponent_character = 'X';
}

int FindBestMove(char board[15][15], char turn, int depth, int alpha, int beta, char& maximaler, char& minimaler,
	short& move_x, short& move_y)
{
	if (depth == 0)
	{
		return EvalBoard(board, maximaler, minimaler);
	}

	char winner = GetWinner(board);
	if (winner != '0')
	{
		return (winner == maximaler) ? INT_MAX : INT_MIN;
	}

	char my_board[15][15];
	memcpy(my_board, board, 225);

	my_board[move_x][move_y] = (turn == minimaler) ? maximaler : minimaler;

	int bestscore = (turn == maximaler) ? INT_MIN : INT_MAX;

	//bool all_moves[15][15];
	//GetAllMoves(my_board, all_moves);

	int eval;
	short seven_minus_i;
	short seven_plus_i;
	short seven_minus_j;
	short seven_plus_j;

	// Finding for maximaler
	if (turn == maximaler)
	{
		for (short i = 0; i <= 7; i++)
		{
			seven_minus_i = 7 - i;
			seven_plus_i = 7 + i;
			for (short j = 0; j <= 7; j++)
			{
				seven_minus_j = 7 - j;
				seven_plus_j = 7 + j;

				if (my_board[seven_minus_j][seven_minus_i] == '0' &&
					((seven_minus_j <= 13 && my_board[seven_minus_j + 1][seven_minus_i] != '0') || (seven_minus_j >= 1 && my_board[seven_minus_j - 1][seven_minus_i] != '0')
						|| (seven_minus_j <= 13 && seven_minus_i <= 13 && my_board[seven_minus_j + 1][seven_minus_i + 1] != '0') || 
						(seven_minus_j >= 1 && seven_minus_i >= 1 && my_board[seven_minus_j - 1][seven_minus_i - 1] != '0')
						|| (seven_minus_j >= 1 && seven_minus_i <= 13 && my_board[seven_minus_j - 1][seven_minus_i + 1] != '0') || 
						(seven_minus_j <= 13 && seven_minus_i >= 1 && my_board[seven_minus_j + 1][seven_minus_i - 1] != '0')
						|| (seven_minus_i <= 13 && my_board[seven_minus_j][seven_minus_i + 1] != '0') || (seven_minus_i >= 1 && my_board[seven_minus_j][seven_minus_i - 1] != '0')))
				{
					eval = FindBestMove(my_board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, seven_minus_j, seven_minus_i);
					bestscore = max(eval, bestscore);
					alpha = max(eval, alpha);
					if (beta <= alpha)
					{
						return bestscore;
					}
				}if (j != 0 && i != 0)
				{
					if (my_board[seven_plus_j][seven_minus_i] == '0' &&
						((seven_plus_j <= 13 && my_board[seven_plus_j + 1][seven_minus_i] != '0') || (seven_plus_j >= 1 && my_board[seven_plus_j - 1][seven_minus_i] != '0')
							|| (seven_plus_j <= 13 && seven_minus_i <= 13 && my_board[seven_plus_j + 1][seven_minus_i + 1] != '0') ||
							(seven_plus_j >= 1 && seven_minus_i >= 1 && my_board[seven_plus_j - 1][seven_minus_i - 1] != '0')
							|| (seven_plus_j >= 1 && seven_minus_i <= 13 && my_board[seven_plus_j - 1][seven_minus_i + 1] != '0') ||
							(seven_plus_j <= 13 && seven_minus_i >= 1 && my_board[seven_plus_j + 1][seven_minus_i - 1] != '0')
							|| (seven_minus_i <= 13 && my_board[seven_plus_j][seven_minus_i + 1] != '0') || (seven_minus_i >= 1 && my_board[seven_plus_j][seven_minus_i - 1] != '0')))
					{
						eval = FindBestMove(my_board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, seven_plus_j, seven_minus_i);
						bestscore = max(eval, bestscore);
						alpha = max(eval, alpha);
						if (beta <= alpha)
						{
							return bestscore;
						}
					}
					if (my_board[seven_minus_j][seven_plus_i] == '0' &&
						((seven_minus_j <= 13 && my_board[seven_minus_j + 1][seven_plus_i] != '0') || (seven_minus_j >= 1 && my_board[seven_minus_j - 1][seven_plus_i] != '0')
							|| (seven_minus_j <= 13 && seven_plus_i <= 13 && my_board[seven_minus_j + 1][seven_plus_i + 1] != '0') ||
							(seven_minus_j >= 1 && seven_plus_i >= 1 && my_board[seven_minus_j - 1][seven_plus_i - 1] != '0')
							|| (seven_minus_j >= 1 && seven_plus_i <= 13 && my_board[seven_minus_j - 1][seven_plus_i + 1] != '0') ||
							(seven_minus_j <= 13 && seven_plus_i >= 1 && my_board[seven_minus_j + 1][seven_plus_i - 1] != '0')
							|| (seven_plus_i <= 13 && my_board[seven_minus_j][seven_plus_i + 1] != '0') || (seven_plus_i >= 1 && my_board[seven_minus_j][seven_plus_i - 1] != '0')))
					{
						eval = FindBestMove(my_board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, seven_minus_j, seven_plus_i);
						bestscore = max(eval, bestscore);
						alpha = max(eval, alpha);
						if (beta <= alpha)
						{
							return bestscore;
						}
					}
					if (my_board[seven_plus_j][seven_plus_i] == '0' &&
						((seven_plus_j <= 13 && my_board[seven_plus_j + 1][seven_plus_i] != '0') || (seven_plus_j >= 1 && my_board[seven_plus_j - 1][seven_plus_i] != '0')
							|| (seven_plus_j <= 13 && seven_plus_i <= 13 && my_board[seven_plus_j + 1][seven_plus_i + 1] != '0') ||
							(seven_plus_j >= 1 && seven_plus_i >= 1 && my_board[seven_plus_j - 1][seven_plus_i - 1] != '0')
							|| (seven_plus_j >= 1 && seven_plus_i <= 13 && my_board[seven_plus_j - 1][seven_plus_i + 1] != '0') ||
							(seven_plus_j <= 13 && seven_plus_i >= 1 && my_board[seven_plus_j + 1][seven_plus_i - 1] != '0')
							|| (seven_plus_i <= 13 && my_board[seven_plus_j][seven_plus_i + 1] != '0') || (seven_plus_i >= 1 && my_board[seven_plus_j][seven_plus_i - 1] != '0')))
					{
						eval = FindBestMove(my_board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, seven_plus_j, seven_plus_i);
						bestscore = max(eval, bestscore);
						alpha = max(eval, alpha);
						if (beta <= alpha)
						{
							return bestscore;
						}
					}
				}
			}
		}
	}
	// Finding for minimaler
	else
	{
		for (short i = 0; i <= 7; i++)
		{
			seven_minus_i = 7 - i;
			seven_plus_i = 7 + i;
			for (short j = 0; j <= 7; j++)
			{
				seven_minus_j = 7 - j;
				seven_plus_j = 7 + j;

				if (my_board[seven_minus_j][seven_minus_i] == '0' &&
					((seven_minus_j <= 13 && my_board[seven_minus_j + 1][seven_minus_i] != '0') || (seven_minus_j >= 1 && my_board[seven_minus_j - 1][seven_minus_i] != '0')
						|| (seven_minus_j <= 13 && seven_minus_i <= 13 && my_board[seven_minus_j + 1][seven_minus_i + 1] != '0') ||
						(seven_minus_j >= 1 && seven_minus_i >= 1 && my_board[seven_minus_j - 1][seven_minus_i - 1] != '0')
						|| (seven_minus_j >= 1 && seven_minus_i <= 13 && my_board[seven_minus_j - 1][seven_minus_i + 1] != '0') ||
						(seven_minus_j <= 13 && seven_minus_i >= 1 && my_board[seven_minus_j + 1][seven_minus_i - 1] != '0')
						|| (seven_minus_i <= 13 && my_board[seven_minus_j][seven_minus_i + 1] != '0') || (seven_minus_i >= 1 && my_board[seven_minus_j][seven_minus_i - 1] != '0')))
				{
					eval = FindBestMove(my_board, maximaler, depth - 1, alpha, beta, maximaler, minimaler, seven_minus_j, seven_minus_i);
					bestscore = min(eval, bestscore);
					beta = min(eval, beta);
					if (beta <= alpha)
					{
						return bestscore;
					}
				}
				if (j != 0 && i != 0)
				{
					if (my_board[seven_plus_j][seven_minus_i] == '0' &&
						((seven_plus_j <= 13 && my_board[seven_plus_j + 1][seven_minus_i] != '0') || (seven_plus_j >= 1 && my_board[seven_plus_j - 1][seven_minus_i] != '0')
							|| (seven_plus_j <= 13 && seven_minus_i <= 13 && my_board[seven_plus_j + 1][seven_minus_i + 1] != '0') ||
							(seven_plus_j >= 1 && seven_minus_i >= 1 && my_board[seven_plus_j - 1][seven_minus_i - 1] != '0')
							|| (seven_plus_j >= 1 && seven_minus_i <= 13 && my_board[seven_plus_j - 1][seven_minus_i + 1] != '0') ||
							(seven_plus_j <= 13 && seven_minus_i >= 1 && my_board[seven_plus_j + 1][seven_minus_i - 1] != '0')
							|| (seven_minus_i <= 13 && my_board[seven_plus_j][seven_minus_i + 1] != '0') || (seven_minus_i >= 1 && my_board[seven_plus_j][seven_minus_i - 1] != '0')))
					{
						eval = FindBestMove(my_board, maximaler, depth - 1, alpha, beta, maximaler, minimaler, seven_plus_j, seven_minus_i);
						bestscore = min(eval, bestscore);
						beta = min(eval, beta);
						if (beta <= alpha)
						{
							return bestscore;
						}
					}
					if (my_board[seven_minus_j][seven_plus_i] == '0' &&
						((seven_minus_j <= 13 && my_board[seven_minus_j + 1][seven_plus_i] != '0') || (seven_minus_j >= 1 && my_board[seven_minus_j - 1][seven_plus_i] != '0')
							|| (seven_minus_j <= 13 && seven_plus_i <= 13 && my_board[seven_minus_j + 1][seven_plus_i + 1] != '0') ||
							(seven_minus_j >= 1 && seven_plus_i >= 1 && my_board[seven_minus_j - 1][seven_plus_i - 1] != '0')
							|| (seven_minus_j >= 1 && seven_plus_i <= 13 && my_board[seven_minus_j - 1][seven_plus_i + 1] != '0') ||
							(seven_minus_j <= 13 && seven_plus_i >= 1 && my_board[seven_minus_j + 1][seven_plus_i - 1] != '0')
							|| (seven_plus_i <= 13 && my_board[seven_minus_j][seven_plus_i + 1] != '0') || (seven_plus_i >= 1 && my_board[seven_minus_j][seven_plus_i - 1] != '0')))
					{
						eval = FindBestMove(my_board, maximaler, depth - 1, alpha, beta, maximaler, minimaler, seven_minus_j, seven_plus_i);
						bestscore = min(eval, bestscore);
						beta = min(eval, beta);
						if (beta <= alpha)
						{
							return bestscore;
						}
					}
					if (my_board[seven_plus_j][seven_plus_i] == '0' &&
						((seven_plus_j <= 13 && my_board[seven_plus_j + 1][seven_plus_i] != '0') || (seven_plus_j >= 1 && my_board[seven_plus_j - 1][seven_plus_i] != '0')
							|| (seven_plus_j <= 13 && seven_plus_i <= 13 && my_board[seven_plus_j + 1][seven_plus_i + 1] != '0') ||
							(seven_plus_j >= 1 && seven_plus_i >= 1 && my_board[seven_plus_j - 1][seven_plus_i - 1] != '0')
							|| (seven_plus_j >= 1 && seven_plus_i <= 13 && my_board[seven_plus_j - 1][seven_plus_i + 1] != '0') ||
							(seven_plus_j <= 13 && seven_plus_i >= 1 && my_board[seven_plus_j + 1][seven_plus_i - 1] != '0')
							|| (seven_plus_i <= 13 && my_board[seven_plus_j][seven_plus_i + 1] != '0') || (seven_plus_i >= 1 && my_board[seven_plus_j][seven_plus_i - 1] != '0')))
					{
						eval = FindBestMove(my_board, maximaler, depth - 1, alpha, beta, maximaler, minimaler, seven_plus_j, seven_plus_i);
						bestscore = min(eval, bestscore);
						beta = min(eval, beta);
						if (beta <= alpha)
						{
							return bestscore;
						}
					} 
				}
			}
		}
	}
	return bestscore;
}

void printBoard(char board[15][15], int right_x_subtstractor, int left_x_subtstractor, int right_y_subtstractor, int left_y_subtstractor)
{
	bool moves[15][15];
	GetAllMoves(board, moves);
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (board[i][j] == 'X')
				cout << "\033[32m" << board[i][j] << " ";
			else if (board[i][j] == 'O')
				cout << "\033[31m" << board[i][j] << " ";
			else if (moves[i][j])
				cout << "\033[33m" << board[i][j] << " ";
			else if (j <= right_x_subtstractor && j >= left_x_subtstractor && i <= right_y_subtstractor && i >= left_y_subtstractor)
				cout << "\033[34m" << board[i][j] << " ";
			else
				cout << "\033[0m" << board[i][j] << " ";

		}
		cout << "\033[0m" << endl;
	}
}


void FindBestScoreInBoardAndReplaceBestIfBetter(int& BestInd, int& BestScore, int& score, char board[15][15], char turn, int depth, int& alpha, int& beta,
	char maximaler, char minimaler, short move_x, short move_y)
{
	score = FindBestMove(board, turn, depth, alpha, beta, maximaler, minimaler, move_x, move_y);
	if (score > BestScore)
	{
		BestScore = score;
		BestInd = (15 * move_x) + move_y;
	}
}

int GetBestMove(string& str_board, char turn, int depth, char maximaler, char minimaler, int left_x_subtstractor, int right_x_subtstractor, int left_y_subtstractor, int right_y_subtstractor)    //function that i will call from python
{
	MinMax* AI = new MinMax(maximaler);
	char board[15][15];

	//converting str 15x15 board to vectors of vector  of chars
	int j = -1;
	for (int i = 0; i < str_board.length(); i++)
	{
		if (i % 15 == 0)
		{
			j++;
		}
		if (str_board[i] == '0' || str_board[i] == 'O' || str_board[i] == 'X')
		{
			board[j][i % 15] = str_board[i];
		}
	}

	bool possible_moves[15][15];
	GetAllMoves(board, possible_moves);

	int bestScore = INT_MIN;
	int temp = 0;
	int BestInd = 0;

	int alpha = INT_MIN;
	int beta = INT_MAX;

	int score1 = 0, score2 = 0, score3 = 0, score4 = 0;

	int seven_minus_i;
	int seven_plus_i;
	int seven_minus_j;
	int seven_plus_j;

	vector<thread> threads;

	for (int i = 0; i <= 7; i++)
	{
		seven_minus_i = 7 - i;
		seven_plus_i = 7 + i;
		for (int j = 0; j <= 7; j++)
		{
			seven_minus_j = 7 - j;
			seven_plus_j = 7 + j;
			if (possible_moves[seven_minus_j][seven_minus_i] && seven_minus_j <= right_x_subtstractor && seven_minus_j >= left_x_subtstractor && seven_minus_i <= right_y_subtstractor && seven_minus_i >= left_y_subtstractor)
			{
				threads.push_back(thread(FindBestScoreInBoardAndReplaceBestIfBetter, ref(BestInd), ref(bestScore), ref(score1), board, AI->Opponent_character, depth - 1, ref(alpha), ref(beta), maximaler, minimaler, seven_minus_j, seven_minus_i));
			}

			if (possible_moves[seven_plus_j][seven_plus_i] && seven_plus_j <= right_x_subtstractor && seven_plus_j >= left_x_subtstractor && seven_plus_i <= right_y_subtstractor && seven_plus_i >= left_y_subtstractor)
			{
				threads.push_back(thread(FindBestScoreInBoardAndReplaceBestIfBetter, ref(BestInd), ref(bestScore), ref(score2), board, AI->Opponent_character, depth - 1, ref(alpha), ref(beta), maximaler, minimaler, seven_plus_j, seven_plus_i));
			}

			if (possible_moves[seven_plus_j][seven_minus_i] && seven_plus_j <= right_x_subtstractor && seven_plus_j >= left_x_subtstractor && seven_minus_i <= right_y_subtstractor && seven_minus_i >= left_y_subtstractor)
			{
				threads.push_back(thread(FindBestScoreInBoardAndReplaceBestIfBetter, ref(BestInd), ref(bestScore), ref(score3), board, AI->Opponent_character, depth - 1, ref(alpha), ref(beta), maximaler, minimaler, seven_plus_j, seven_minus_i));
			}

			if (possible_moves[seven_minus_j][seven_plus_i] && seven_minus_j <= right_x_subtstractor && seven_minus_j >= left_x_subtstractor && seven_plus_i <= right_y_subtstractor && seven_plus_i >= left_y_subtstractor)
			{
				threads.push_back(thread(FindBestScoreInBoardAndReplaceBestIfBetter, ref(BestInd), ref(bestScore), ref(score4), board, AI->Opponent_character, depth - 1, ref(alpha), ref(beta), maximaler, minimaler, seven_minus_j, seven_plus_i));
			}
		}
	}

	for (int i = 0; i < threads.size(); i++)
	{
		if (i % 4 == 0)
		{
			cout << (float)i / threads.size() << endl;
		}
		threads[i].join();
	}

	return BestInd;
}

char GetWinner(char board[15][15])
{
	int i_minus_sth[4];
	for (int i = 0; i <= 14; i++)
	{
		i_minus_sth[3] = i - 4;
		i_minus_sth[2] = i - 3;
		i_minus_sth[1] = i - 2;
		i_minus_sth[0] = i - 1;
		for (int j = 0; j <= 14; j++)
		{
			if (board[i][j] != '0')
			{
				// Checking column
				if (i >= 4 && board[i][j] == board[i_minus_sth[0]][j] && board[i_minus_sth[0]][j] == board[i_minus_sth[1]][j]
					&& board[i_minus_sth[1]][j] == board[i_minus_sth[2]][j] && board[i_minus_sth[2]][j] == board[i_minus_sth[3]][j])
				{
					if (i > 4 && ((i == 14 || board[i + 1][j] != board[i][j]) && board[i][j] != board[i - 5][j]))
					{
						return board[i][j];
					}
					if (i == 4 && board[i + 1][j] != board[i][j])
					{
						return board[i][j];
					}
				}

				if (j >= 4)
				{
					//checking row
					if (board[i][j] == board[i][j - 1] && board[i][j - 1] == board[i][j - 2]
						&& board[i][j - 2] == board[i][j - 3] && board[i][j - 3] == board[i][j - 4])
					{
						if (j > 4 && (j == 14 || board[i][j + 1] != board[i][j]) && board[i][j - 5] != board[i][j])
						{
							return board[i][j];
						}
						if (j == 4 && board[i][5] != board[i][j])
						{
							return board[i][j];
						}
					}
					//checking diagnals from upper left to bottom right
					if (i >= 4 && board[i][j] == board[i_minus_sth[0]][j - 1] && board[i_minus_sth[0]][j - 1] == board[i_minus_sth[1]][j - 2]
						&& board[i_minus_sth[1]][j - 2] == board[i_minus_sth[2]][j - 3] && board[i_minus_sth[2]][j - 3] == board[i_minus_sth[3]][j - 4])
					{
						if (i > 4 && j > 4 && ((i == 14 || j == 14) || board[i][j] != board[i + 1][j + 1]) && board[i][j] != board[i - 5][j - 5])
						{
							return board[i][j];
						}
						if (i == 4 && j == 4 && board[i][j] != board[i + 1][j + 1])
						{
							return board[i][j];
						}
					}
					//checking diagnals from upper right to bottom left
					if (i <= 10 && board[i][j] == board[i + 1][j - 1] && board[i + 1][j - 1] == board[i + 2][j - 2]
						&& board[i + 2][j - 2] == board[i + 3][j - 3] && board[i + 3][j - 3] == board[i + 4][j - 4])
					{
						if (i < 10 && j > 4 && ((i == 0 || j == 14) || board[i][j] != board[i - 1][j + 1]) && board[i][j] != board[i + 5][j - 5])
						{
							return board[i][j];
						}
						if (i == 10 && j == 4 && board[i][j] != board[9][5])
						{
							return board[i][j];
						}
					}
				}
			}
		}
	}
	return '0';
}
//return 15x15 board filled with bool. If field is true then its valid move
void GetAllMoves(char board[15][15], bool moves[15][15])
{
	for (int i = 0; i <= 14; i++)
	{
		for (int j = 0; j <= 14; j++)
		{
			if (board[i][j] == '0' &&
				((i <= 13 && board[i + 1][j] != '0') || (i >= 1 && board[i - 1][j] != '0')
					|| (i <= 13 && j <= 13 && board[i + 1][j + 1] != '0') || (i >= 1 && j >= 1 && board[i - 1][j - 1] != '0')
					|| (i >= 1 && j <= 13 && board[i - 1][j + 1] != '0') || (i <= 13 && j >= 1 && board[i + 1][j - 1] != '0')
					|| (j <= 13 && board[i][j + 1] != '0') || (j >= 1 && board[i][j - 1] != '0')))
				moves[i][j] = true;
			else
				moves[i][j] = false;
		}
	}
}

//Evalueate the board
int EvalBoard(char board[15][15], char& maximaler, char& minimaler)
{
	return ScoreBoard(board, maximaler, minimaler);
}

int ScoreBoard(char board[15][15], char& maximaler, char& minimaler) //AI +, player -
{
	int i_minus_sth[4];
	int score = 0;
	for (int i = 0; i <= 14; i++)
	{
		i_minus_sth[3] = i - 4;
		i_minus_sth[2] = i - 3;
		i_minus_sth[1] = i - 2;
		i_minus_sth[0] = i - 1;
		for (int j = 0; j <= 14; j++)
		{
			if (board[i][j] != '0')
			{
				// Checking column
				if (i >= 4)
				{
					if (board[i][j] == board[i_minus_sth[0]][j] && board[i_minus_sth[0]][j] == board[i_minus_sth[1]][j])
					{
						//0XXXX or XXXX0 or win/lose
						if (board[i_minus_sth[1]][j] == board[i_minus_sth[2]][j])
						{
							if (board[i_minus_sth[3]][j] == '0' && ((i != 14 && board[i + 1][j] == '0')))
								return (board[i][j] == maximaler) ? INT_MAX / 2 : INT_MIN / 2;
							if (board[i_minus_sth[3]][j] == '0' || (i != 14 && board[i + 1][j] == '0'))
								score += (board[i][j] == maximaler) ? 2 : -2;
							if (board[i_minus_sth[3]][j] == board[i][j] || (i != 14 && board[i + 1][j] == board[i][j]))
								return (board[i][j] == maximaler) ? INT_MAX : INT_MIN;
						}
						//check column X0XXX
						else if (board[i_minus_sth[2]][j] == '0' && board[i_minus_sth[3]][j] == board[i][j])
						{
							score += (board[i][j] == maximaler) ? 2 : -2;
						}
					}
					else if (board[i_minus_sth[2]][j] == board[i][j] && board[i_minus_sth[3]][j] == board[i][j])
					{
						//check column XX0XX
						if (board[i][j] == board[i_minus_sth[0]][j] && board[i_minus_sth[1]][j] == '0')
						{
							score += (board[i][j] == maximaler) ? 2 : -2;
						}
						//check column XXX0X
						else if (board[i][j] == board[i_minus_sth[1]][j] && board[i_minus_sth[0]][j] == '0')
						{
							score += (board[i][j] == maximaler) ? 2 : -2;
						}
					}
				}

				if (j >= 4)
				{
					//checking row
					if (board[i][j] == board[i][j - 1] && board[i][j - 1] == board[i][j - 2])
					{
						//0XXXX or XXXX0 or win/lose
						if (board[i][j - 2] == board[i][j - 3])
						{
							if (board[i][j - 4] == '0' && (j != 14 && board[i][j + 1] == '0'))
								return (board[i][j] == maximaler) ? INT_MAX / 2 : INT_MIN / 2;
							if (board[i][j - 4] == board[i][j] || (j != 14 && board[i][j + 1] == board[i][j]))
								return (board[i][j] == maximaler) ? INT_MAX : INT_MIN;
							if (board[i][j - 4] == '0' || (j != 14 && board[i][j + 1] == '0'))
								score += (board[i][j] == maximaler) ? 2 : -2;
						}
						//check column X0XXX
						else if (board[i][j - 3] == '0' && board[i][j - 4] == board[i][j])
						{
							score += (board[i][j] == maximaler) ? 2 : -2;
						}
					}
					else if (board[i][j - 3] == board[i][j] && board[i][j - 4] == board[i][j])
					{
						//check column XX0XX
						if (board[i][j] == board[i][j - 1] && board[i][j - 2] == '0')
						{
							score += (board[i][j] == maximaler) ? 2 : -2;
						}
						//check column XXX0X
						else if (board[i][j] == board[i][j - 2] && board[i][j - 1] == '0')
						{
							score += (board[i][j] == maximaler) ? 2 : -2;
						}

					}

					//checking diagnals from upper left to bottom right
					if (i >= 4)
					{
						if (board[i][j] == board[i_minus_sth[0]][j - 1] && board[i_minus_sth[0]][j - 1] == board[i_minus_sth[1]][j - 2])
						{
							//0XXXX or XXXX0 or win/lose
							if (board[i_minus_sth[1]][j - 2] == board[i_minus_sth[2]][j - 3])
							{
								if (board[i_minus_sth[3]][j - 4] == '0' && ((i != 14 && j != 14) && board[i + 1][j + 1] == '0'))
									return (board[i][j] == maximaler) ? INT_MAX / 2 : INT_MIN / 2;
								if (board[i_minus_sth[3]][j - 4] == '0' || board[i + 1][j + 1] == '0')
									score += (board[i][j] == maximaler) ? 2 : -2;
								if (board[i_minus_sth[3]][j - 4] == board[i][j] || board[i + 1][j + 1] == board[i][j])
									return (board[i][j] == maximaler) ? INT_MAX : INT_MIN;
							}
							//checking diagnals X0XXX
							else if (board[i_minus_sth[2]][j - 3] == '0' && board[i_minus_sth[3]][j - 4] == board[i][j])
							{
								score += (board[i][j] == maximaler) ? 2 : -2;
							}
						}
						if (board[i_minus_sth[2]][j - 3] == board[i][j] && board[i_minus_sth[3]][j - 4] == board[i][j])
						{
							//checking diagnals XX0XX
							if (board[i][j] == board[i_minus_sth[0]][j - 1] && board[i_minus_sth[1]][j - 2] == '0')
							{
								score += (board[i][j] == maximaler) ? 2 : -2;
							}
							//checking diagnals XXX0X
							else if (board[i][j] == board[i_minus_sth[1]][j - 2] && board[i_minus_sth[0]][j - 1] == '0')
							{
								score += (board[i][j] == maximaler) ? 2 : -2;
							}
						}
					}

					//checking diagnals from upper right to bottom left
					if (i <= 10)
					{
						if (board[i][j] == board[i + 1][j - 1] && board[i + 1][j - 1] == board[i + 2][j - 2])
						{
							//0XXXX or XXXX0 or win/lose
							if (board[i + 2][j - 2] == board[i + 3][j - 3])
							{
								if (board[i + 4][j - 4] == '0' && (i != 0 && j != 14 && board[i - 1][j + 1] == '0'))
									return (board[i][j] == maximaler) ? INT_MAX / 2 : INT_MIN / 2;
								if (board[i + 4][j - 4] == '0' || (i != 0 && j != 14 && board[i - 1][j + 1] == '0'))
									score += (board[i][j] == maximaler) ? 2 : -2;
								if (board[i + 4][j - 4] == board[i][j] || board[i - 1][j + 1] == board[i][j])
									return (board[i][j] == maximaler) ? INT_MAX : INT_MIN;
							}
							//checking diagnals X0XXX
							else if (board[i + 3][j - 3] == '0' && board[i + 4][j - 4] == board[i][j])
							{
								score += (board[i][j] == maximaler) ? 2 : -2;
							}
						}
						else if (board[i + 3][j - 3] == board[i][j] && board[i + 4][j - 4] == board[i][j])
						{
							//checking diagnals XX0XX
							if (board[i][j] == board[i + 1][j - 1] && board[i + 2][j - 2] == '0')
							{
								score += (board[i][j] == maximaler) ? 2 : -2;
							}
							//checking diagnals XX0XX
							if (board[i][j] == board[i + 2][j - 2] && board[i + 1][j - 1] == '0')
							{
								score += (board[i][j] == maximaler) ? 2 : -2;
							}
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
	bool making_data = false;
	bool print_board = true;
	int depth = 5;

	int left_x_subtstractor = 0, right_x_subtstractor = 14, left_y_subtstractor = 0, right_y_subtstractor = 14;
	string str_board;

	int indexes_range;
	if (making_data)
		//indexes_range = 255;
		indexes_range = 195;
	else
		indexes_range = 1;

	for (int index = 0; index < indexes_range; index++)
	{

		if (making_data)
		{
			while (index % 15 < 3 || index % 15 > 11) index++;	//bc first wanna predict more possiblem opponent moves

			cout << "INDEX: " << index << endl;
			str_board = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
			str_board[112] = 'X';
			while (str_board[index] != '0' && index <= 224)
				index += 1;
			str_board[index] = 'O';
		}
		else
		{
			fstream board_file;
			board_file.open("board.txt", ios::in);
			board_file >> str_board >> depth >> left_x_subtstractor >> right_x_subtstractor >> left_y_subtstractor >> right_y_subtstractor;
			board_file.close();
		}

		// if board is empty, go middle
		bool only_zeros = true;
		for (int i = 0; i < str_board.length(); i++)
		{
			if (str_board[i] != '0')
			{
				only_zeros = false;
				break;
			}
		}
		if (only_zeros)
		{
			fstream return_file;
			return_file.open("string_index_return.txt", ios::out);
			return_file << 112;
			return_file.close();
			return 0;
		}

		/// FINDING BEST MOVE
		const clock_t begin_time = clock();
		int move = 0;
		move = GetBestMove(str_board, 'X', depth, 'X', 'O', left_x_subtstractor, right_x_subtstractor, left_y_subtstractor, right_y_subtstractor);


		char board[15][15];
		if (print_board)
		{
			cout << "MOVE: " << move % 15 << " " << (int)move / 15 << endl;
			cout << "MOVE: " << move << " " << endl;
			cout << "IT TOOK: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

			str_board[move] = 'X';
			// COnvertign str_board to chars board
			int j = -1;
			for (int i = 0; i < str_board.length(); i++)
			{
				if (i % 15 == 0)
				{
					j++;
				}
				if (str_board[i] == '0' || str_board[i] == 'O' || str_board[i] == 'X')
				{
					board[j][i % 15] = str_board[i];
				}
			}

			printBoard(board, right_x_subtstractor, left_x_subtstractor, right_y_subtstractor, left_y_subtstractor);
		}

		// Saving temp best move
		fstream return_file;
		return_file.open("string_index_return.txt", ios::out);
		return_file << move;
		return_file.close();

		//CREATING DATA
		fstream calculated_moves;
		if (making_data)
		{
			calculated_moves.open("calculated_moves.txt", ios::app);
			calculated_moves << (string)str_board << " ; " << move << endl;	///UN COMMENT TO MAKE DATA
			calculated_moves.close();
		}
	}
	return 0;
}

//board to test: 000000000000000000000000000000000000000000000000000000000000000000000X000000000000XO00000000000OOO000000000000XOX000000000000O0X00000000000XO0X0000000000000000000000000000000000000000000000000000000000000000000000000000000000