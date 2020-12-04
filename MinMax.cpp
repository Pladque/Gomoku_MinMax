#include <vector>
#include <iostream>
//#include <bits/stdc++.h>    //min max int values
#include <map>              //hashmaps
#include <chrono>			//clock

using namespace std;

///OPTYMALIZATION IDEAS ///
//1 instead of checing if char is 'X' or 'O' ot '0' etc just do sth like "if 3. bit is 1, then its 0 so..."
//2. in GetAmountOf_4_OR_3_InRow store values like "7-1, etc"	DONE
//3. change x_substractor to left_x_substractor and right_x_substracotr, same with y
//4. Made data base from best moves for first few steps
//5. watch some gumoku tutorials, they mayu be helpful

int GetAmountOf_4_OR_3_InRow(vector<vector<char>>& board, char& maximaler, char& minimaler, int x_substractor = 0, int y_substractor = 0);
int EvalBoard(vector<vector<char>>& board, char& maximaler, char& minimaler, int x_substractor = 0, int y_substractor = 0);
void GetAllMoves(vector<vector<char>>& board, vector<vector<bool>>& moves);
char GetWinner(vector<vector<char>>& board, int x_substractor = 0, int y_substractor = 0);

//vector<vector<vector<char>>> ALLBOARDS;
map<vector<vector<char>>, int> ALLBOARDS;


class MinMax
{
private:
public:
	char AI_character;
	char Opponent_character;
	MinMax(char AI_Char);
	int FindBestMove(vector<vector<char>> board, char turn, int depth, int& alpha, int& beta, char maximaler, char minimaler, int move_x, int move_y, int& x_substractor, int& y_substractor);
};

MinMax::MinMax(char AI_Char)
{
	AI_character = AI_Char;
	if (AI_Char == 'X')
		Opponent_character = 'O';
	else
		Opponent_character = 'X';

}

int MinMax::FindBestMove(vector<vector<char>> board, char turn, int depth, int& alpha, int& beta, char maximaler, char minimaler, int move_x, int move_y, int& x_substractor, int& y_substractor)
{
	if (depth == 0)
	{
		return EvalBoard(board, maximaler, minimaler, x_substractor, y_substractor);
	}

	char winner = GetWinner(board, x_substractor, y_substractor);
	if (winner != '0')
		return (winner = maximaler) ? INT_MAX : INT_MIN;

	int bestscore = (turn == maximaler) ? INT_MIN : INT_MAX;
	board[move_x][move_y] = (turn == minimaler) ? maximaler : minimaler;

	//skipping already considered boards:
	if (ALLBOARDS.find(board) != ALLBOARDS.end())
	{
		return ALLBOARDS[board];
	}

	vector<vector<bool>> all_moves;
	GetAllMoves(board, all_moves);
	int eval;

	int seven_minus_i;
	int seven_plus_i;
	// Finding for maximaler
	if (turn == maximaler)
	{
		for (int i = 0; i <= 7 - y_substractor; i++)
		{
			seven_minus_i = 7 - i;
			seven_plus_i = 7 + i;
			for (int j = 0; j <= 7 - x_substractor; j++)
			{
				if (all_moves[7 - j][seven_minus_i])
				{
					eval = FindBestMove(board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, 7 - j, seven_minus_i, x_substractor, y_substractor);
					bestscore = max(eval, bestscore);
					alpha = max(eval, alpha);
					if (beta <= alpha)
					{
						ALLBOARDS[board] = bestscore;
						//board[move_x][move_y] = '0';
						return bestscore;
					}
				}if (all_moves[7 + j][seven_minus_i] && j != 0 && i != 0)
				{
					eval = FindBestMove(board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, 7 + j, seven_minus_i, x_substractor, y_substractor);
					bestscore = max(eval, bestscore);
					alpha = max(eval, alpha);
					if (beta <= alpha)
					{
						ALLBOARDS[board] = bestscore;
						//board[move_x][move_y] = '0';
						return bestscore;
					}
				}if (all_moves[7 - j][seven_plus_i] && j != 0 && i != 0)
				{
					eval = FindBestMove(board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, 7 - j, seven_plus_i, x_substractor, y_substractor);
					bestscore = max(eval, bestscore);
					alpha = max(eval, alpha);
					if (beta <= alpha)
					{
						ALLBOARDS[board] = bestscore;
						//board[move_x][move_y] = '0';
						return bestscore;
					}
				}if (all_moves[7 + j][seven_plus_i] && j != 0 && i != 0)
				{
					eval = FindBestMove(board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, 7 + j, seven_plus_i, x_substractor, y_substractor);
					bestscore = max(eval, bestscore);
					alpha = max(eval, alpha);
					if (beta <= alpha)
					{
						ALLBOARDS[board] = bestscore;
						//board[move_x][move_y] = '0';
						return bestscore;
					}
				}

			}
		}
	}
	// Finding for minimaler
	else
	{
		for (int i = 0; i <= 7 - y_substractor; i++)
		{
			seven_minus_i = 7 - i;
			seven_plus_i = 7 + i;
			for (int j = 0; j <= 7 - x_substractor; j++)
			{
				if (all_moves[7 - j][seven_minus_i])
				{
					eval = FindBestMove(board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, 7 - j, seven_minus_i, x_substractor, y_substractor);
					bestscore = min(eval, bestscore);
					beta = min(eval, beta);
					if (beta <= alpha)
					{
						ALLBOARDS[board] = bestscore;
						//board[move_x][move_y] = '0';
						return bestscore;
					}
				} if (all_moves[7 + j][seven_minus_i] && j != 0 && i != 0)
				{
					eval = FindBestMove(board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, 7 + j, seven_minus_i, x_substractor, y_substractor);
					bestscore = min(eval, bestscore);
					beta = min(eval, beta);
					if (beta <= alpha)
					{
						ALLBOARDS[board] = bestscore;
						//board[move_x][move_y] = '0';
						return bestscore;
					}
				}if (all_moves[7 + j][seven_plus_i] && j != 0 && i != 0)
				{
					eval = FindBestMove(board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, 7 + j, seven_plus_i, x_substractor, y_substractor);
					bestscore = min(eval, bestscore);
					beta = min(eval, beta);
					if (beta <= alpha)
					{
						ALLBOARDS[board] = bestscore;
						//board[move_x][move_y] = '0';
						return bestscore;
					}
				} if (all_moves[7 - j][seven_plus_i] && j != 0 && i != 0)
				{
					eval = FindBestMove(board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, 7 - j, seven_plus_i, x_substractor, y_substractor);
					bestscore = min(eval, bestscore);
					beta = min(eval, beta);
					if (beta <= alpha)
					{
						ALLBOARDS[board] = bestscore;
						//board[move_x][move_y] = '0';
						return bestscore;
					}

				}

			}
		}

	}
	ALLBOARDS[board] = bestscore;
	//board[move_x][move_y] = '0';
	return bestscore;
}

int GetBestMove(string &str_board, char turn, int depth, char maximaler, char minimaler, int x_substractor, int  y_substractor)    //function that i will call from python
{
	MinMax* AI = new MinMax(maximaler);
	vector<vector<char>> board;

	//converting str 15x15 board to vectors of vector  of chars
	for (int i = 0; i < str_board.length(); i++)
	{
		if (i % 15 == 0)
		{
			vector<char> empty_vec;
			board.push_back(empty_vec);
		}
		if (str_board[i] == '0' || str_board[i] == 'O' || str_board[i] == 'X')
		{
			board[(int)i / 15].push_back(str_board[i]);
		}
	}

	vector<vector<bool>> possible_moves;
	GetAllMoves(board, possible_moves);
	int bestScore = INT_MIN;
	int temp;
	int BestInd;

	int alpha = INT_MIN;
	int beta = INT_MAX;

	for (int i = 0; i <= 7 - y_substractor; i++)
	{
		for (int j = 0; j <= 7 - x_substractor; j++)
		{
			cout << i << " " << j << endl;
			if (possible_moves[7 - j][7 - i])
			{
				temp = AI->FindBestMove(board, AI->Opponent_character, depth - 1, alpha, beta, maximaler, minimaler, 7 - j, 7 - i, x_substractor, y_substractor);
				if (temp > bestScore)
				{
					bestScore = temp;
					BestInd = 112 - (15 * j) - i;                //(7-j)*15 + 7-i;
				}

				if (bestScore == INT_MAX) return BestInd;
			}if (possible_moves[7 + j][7 + i])
			{
				temp = AI->FindBestMove(board, AI->Opponent_character, depth - 1, alpha, beta, maximaler, minimaler, 7 + j, 7 + i, x_substractor, y_substractor);
				if (temp > bestScore)
				{
					bestScore = temp;
					BestInd = (15 * j) + 112 + i;
				}

				if (bestScore == INT_MAX) return BestInd;
			}if (possible_moves[7 + j][7 - i])
			{
				temp = AI->FindBestMove(board, AI->Opponent_character, depth - 1, alpha, beta, maximaler, minimaler, 7 + j, 7 - i, x_substractor, y_substractor);
				if (temp > bestScore)
				{
					bestScore = temp;
					BestInd = (15 * j) + 112 - i;

				}

				if (bestScore == INT_MAX) return BestInd;
			}if (possible_moves[7 - j][7 + i])
			{
				temp = AI->FindBestMove(board, AI->Opponent_character, depth - 1, alpha, beta, maximaler, minimaler, 7 - j, 7 + i, x_substractor, y_substractor);
				if (temp > bestScore)
				{
					bestScore = temp;
					BestInd = 112 - (15 * j) + i;
				}

				if (bestScore == INT_MAX) return BestInd;
			}
		}
	}
	return BestInd;
}

char GetWinner(vector<vector<char>>& board, int x_substractor, int y_substractor)
{
	int i_minus_sth[4];
	for (int i = y_substractor; i <= 14 - y_substractor; i++)
	{
		i_minus_sth[3] = i - 4;
		i_minus_sth[2] = i - 3;
		i_minus_sth[1] = i - 2;
		i_minus_sth[0] = i - 1;
		for (int j = x_substractor; j <= 14 - x_substractor; j++)
		{
			if (board[i][j] != '0')
			{
				// Checking column
				if (i >= 4 && board[i][j] == board[i_minus_sth[0]][j] && board[i_minus_sth[0]][j] == board[i_minus_sth[1]][j]
					&& board[i_minus_sth[1]][j] == board[i_minus_sth[2]][j] && board[i_minus_sth[2]][j] == board[i_minus_sth[3]][j])
				{
					return board[i][j];
				}
				//checking row
				if (j >= 4 && board[i][j] == board[i][j - 1] && board[i][j - 1] == board[i][j - 2]
					&& board[i][j - 2] == board[i][j - 3] && board[i][j - 3] == board[i][j - 4])
				{
					return board[i][j];
				}
				//checking diagnals from upper left to bottom right
				if (i >= 4 && j >= 4 && board[i][j] == board[i_minus_sth[0]][j - 1] && board[i_minus_sth[0]][j - 1] == board[i_minus_sth[1]][j - 2]
					&& board[i_minus_sth[1]][j - 2] == board[i_minus_sth[2]][j - 3] && board[i_minus_sth[2]][j - 3] == board[i_minus_sth[3]][j - 4])
				{
					return board[i][j];
				}
				//checking diagnals from upper right to bottom left
				if (i <= 10 && j >= 4 && board[i][j] == board[i + 1][j - 1] && board[i + 1][j - 1] == board[i + 2][j - 2]
					&& board[i + 2][j - 2] == board[i + 3][j - 3] && board[i + 3][j - 3] == board[i + 4][j - 4])
				{
					return board[i][j];
				}
			}
		}
	}

	return '0';
}

//return 15x15 board, if value is true, valid move
void GetAllMoves(vector<vector<char>>& board, vector<vector<bool>>& moves)
{
	//vector<vector<bool>> moves;
	for (int i = 0; i <= 14; i++)
	{
		vector<bool> empty_vec;
		moves.push_back(empty_vec);
		for (int j = 0; j <= 14; j++)
		{
			if (board[i][j] == '0')
				moves[i].push_back(true);
			else
				moves[i].push_back(false);
		}
	}

}

//I need winner seperaty!!!
int EvalBoard(vector<vector<char>>& board, char& maximaler, char& minimaler, int x_substractor, int y_substractor)
{
	switch (GetWinner(board, x_substractor, y_substractor))
	{
	case 'X':
		return INT_MAX;
	case 'O':
		return INT_MIN;
	default:
		return GetAmountOf_4_OR_3_InRow(board, maximaler, minimaler, x_substractor, y_substractor);
	}

}

int GetAmountOf_4_OR_3_InRow(vector<vector<char>>& board, char& maximaler, char& minimaler, int x_substractor, int y_substractor) //AI +, player -
{
	int plus_score = 0;
	int minus_score = 0;
	int amount_of_maximaler_temp;
	int i_minus_sth[4];
	for (int i = y_substractor; i <= 14 - y_substractor; i++)
	{
		i_minus_sth[3] = i - 4;
		i_minus_sth[2] = i - 3;
		i_minus_sth[1] = i - 2;
		i_minus_sth[0] = i - 1;
		for (int j = x_substractor; j <= 14 - x_substractor; j++)
		{
			amount_of_maximaler_temp = 0;
			if (board[i][j] == maximaler)
			{
				// Checking row
				if (i >= 4)
				{
					if (!(board[i_minus_sth[3]][j] == minimaler || board[i_minus_sth[2]][j] == minimaler
						|| board[i_minus_sth[1]][j] == minimaler || board[i_minus_sth[0]][j] == minimaler))
					{
						if (board[i][j] == board[i_minus_sth[0]][j])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i_minus_sth[1]][j])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i_minus_sth[2]][j])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i_minus_sth[3]][j])
						{
							amount_of_maximaler_temp++;
						};

						if (amount_of_maximaler_temp >= 3)
						{
							plus_score += 2;
						}
						else if (amount_of_maximaler_temp == 2)
						{
							plus_score += 1;
						}
					}

					amount_of_maximaler_temp = 0;
					//checking diagnals from bottom left to upper right
					if (j >= 4)
					{
						if (!(board[i_minus_sth[3]][j - 4] == minimaler || board[i_minus_sth[2]][j - 3] == minimaler
							|| board[i_minus_sth[1]][j - 2] == minimaler || board[i_minus_sth[0]][j - 1] == minimaler))
						{
							if (board[i][j] == board[i_minus_sth[0]][j - 1])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[1]][j - 2])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[2]][j - 3])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[3]][j - 4])
							{
								amount_of_maximaler_temp++;
							};

							if (amount_of_maximaler_temp >= 3)
							{
								plus_score += 2;
							}
							else if (amount_of_maximaler_temp == 2)
							{
								plus_score += 1;
							}
						}

					}
					//checking diagnals from bottom left to upper right     
					if (j <= 10)
					{
						if (!(board[i_minus_sth[3]][j + 4] == minimaler || board[i_minus_sth[2]][j + 3] == minimaler
							|| board[i_minus_sth[1]][j + 2] == minimaler || board[i_minus_sth[0]][j + 1] == minimaler))
						{
							if (board[i][j] == board[i_minus_sth[0]][j + 1])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[1]][j + 2])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[2]][j + 3])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[3]][j + 4])
							{
								amount_of_maximaler_temp++;
							};

							if (amount_of_maximaler_temp >= 3)
							{
								plus_score += 2;
							}
							else if (amount_of_maximaler_temp == 2)
							{
								plus_score += 1;
							}
						}
					}
				}
				amount_of_maximaler_temp = 0;
				if (j >= 4)
				{
					//checking column
					if (!(board[i][j - 4] == minimaler || board[i][j - 3] == minimaler
						|| board[i][j - 2] == minimaler || board[i][j - 1] == minimaler))
					{
						if (board[i][j] == board[i][j - 1])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i][j - 2])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i][j - 3])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i][j - 4])
						{
							amount_of_maximaler_temp++;
						}

						if (amount_of_maximaler_temp >= 3)
						{
							plus_score += 2;
						}
						else if (amount_of_maximaler_temp == 2)
						{
							plus_score += 1;
						}
					}


				}

			}
			else if (board[i][j] == minimaler)
			{
				if (i >= 4)
				{
					// Checking row
					if (!(board[i_minus_sth[3]][j] == maximaler || board[i_minus_sth[2]][j] == maximaler
						|| board[i_minus_sth[1]][j] == maximaler || board[i_minus_sth[0]][j] == maximaler))
					{
						if (board[i][j] == board[i_minus_sth[0]][j])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i_minus_sth[1]][j])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i_minus_sth[2]][j])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i_minus_sth[3]][j])
						{
							amount_of_maximaler_temp++;
						};

						if (amount_of_maximaler_temp >= 3)
						{
							minus_score -= 2;
						}
						else if (amount_of_maximaler_temp == 2)
						{
							minus_score -= 1;
						}
					}

					amount_of_maximaler_temp = 0;
					if (j <= 10)
					{
						//checking diagnals from bottom left to upper right     
						if (!(board[i_minus_sth[3]][j + 4] == maximaler || board[i_minus_sth[2]][j + 3] == maximaler
							|| board[i_minus_sth[1]][j + 2] == maximaler || board[i_minus_sth[0]][j + 1] == maximaler))
						{
							if (board[i][j] == board[i_minus_sth[0]][j + 1])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[1]][j + 2])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[2]][j + 3])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[3]][j + 4])
							{
								amount_of_maximaler_temp++;
							};

							if (amount_of_maximaler_temp >= 3)
							{
								minus_score -= 2;
							}
							else if (amount_of_maximaler_temp == 2)
							{
								minus_score -= 1;
							}
						}
					}

					if (j >= 4)
					{
						//checking diagnals from bottom left to upper right
						if (!(board[i_minus_sth[3]][j - 4] == maximaler || board[i_minus_sth[2]][j - 3] == maximaler
							|| board[i_minus_sth[1]][j - 2] == maximaler || board[i_minus_sth[0]][j - 1] == maximaler))
						{
							if (board[i][j] == board[i_minus_sth[0]][j - 1])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[1]][j - 2])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[2]][j - 3])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[3]][j - 4])
							{
								amount_of_maximaler_temp++;
							};

							if (amount_of_maximaler_temp >= 3)
							{
								minus_score -= 2;
							}
							else if (amount_of_maximaler_temp == 2)
							{
								minus_score -= 1;
							}
						}

					}


				}
				amount_of_maximaler_temp = 0;
				if (j >= 4)
				{
					//checking column
					if (!(board[i][j - 4] == maximaler || board[i][j - 3] == maximaler
						|| board[i][j - 2] == maximaler || board[i][j - 1] == maximaler))
					{
						if (board[i][j] == board[i][j - 1])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i][j - 2])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i][j - 3])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i][j - 4])
						{
							amount_of_maximaler_temp++;
						};

						if (amount_of_maximaler_temp >= 3)
						{
							minus_score -= 2;
						}
						else if (amount_of_maximaler_temp == 2)
						{
							minus_score -= 1;
						}
					}
				}
				if (minus_score < -5) return INT_MIN;   //bc thats mean that opponent has a lot of possibilities
				amount_of_maximaler_temp = 0;
			}
		}
	}
	return plus_score + minus_score;
}


int main()
{
	string str_board = "000000000000000000000000000000000000000000000000000000000000000000000000X0XX0000000000000000000X0XXO00OO00000000000000XX0X0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

	vector<vector<char>> board;
	//converting str 15x15 board to vectors of vector  of chars
	for (int i = 0; i < str_board.length(); i++)
	{
		if (i % 15 == 0)
		{
			vector<char> empty_vec;
			board.push_back(empty_vec);
		}
		if (str_board[i] == '0' || str_board[i] == 'O' || str_board[i] == 'X')
		{
			board[(int)i / 15].push_back(str_board[i]);
		}
	}
	/// Schowing changed board
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (board[i][j] == 'X')
				cout << "\033[32m" << board[i][j] << " ";
			else if (board[i][j] == 'O')
				cout << "\033[31m" << board[i][j] << " ";
			else
			{
				cout << "\033[0m" << board[i][j] << " ";
			}

		}
		cout << endl;
	}

	cout << endl; cout << endl; cout << endl; cout << endl; cout << endl;
	/// FINDING BEST
	const clock_t begin_time = clock();
	int move = GetBestMove(str_board, 'X', 3, 'X', 'O', 0, 0);
	cout << "MOVE: " << move << endl;

	cout << "IT TOOK: " << float(clock() - begin_time) / CLOCKS_PER_SEC<<endl;
	str_board[move] = 'X';

	//converting str 15x15 board to vectors of vector  of chars
	board.clear();
	for (int i = 0; i < str_board.length(); i++)
	{
		if (i % 15 == 0)
		{
			vector<char> empty_vec;
			board.push_back(empty_vec);
		}
		if (str_board[i] == '0' || str_board[i] == 'O' || str_board[i] == 'X')
		{
			board[(int)i / 15].push_back(str_board[i]);
		}
	}

	//making opponent move
	//str_board[100] = 'O';
	//str_board[101] = 'O';

	/// Schowing changed board
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (board[i][j] == 'X')
				cout << "\033[32m" << board[i][j] << " ";
			else if (board[i][j] == 'O')
				cout << "\033[31m" << board[i][j] << " ";
			else
			{
				cout << "\033[0m" << board[i][j] << " ";
			}

		}
		cout << endl;
	}


	
}
