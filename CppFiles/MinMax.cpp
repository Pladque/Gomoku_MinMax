#include <vector>
#include <iostream>
#include <map>					//hashmaps
#include <chrono>				//clock
#include <thread>
#include <fstream>
#include <cstdlib>
//#include <bits/stdc++.h>		//min max int values

using namespace std;

///OPTYMALIZATION IDEAS ///
//4. Made data base from best moves for first few steps
//6. clean up code
//7. add file where i will save best moves
//8. Build it, and run .exe from python (use file to communicate python<->cpp)
//11. try some optymalization (group ifs,less math etc)
//12. mby add substracorts to Board Ealuation
//13. to GetWinner add checking if there are  exacly 5 in row(and not f.e 6)

int GetAmountOf_4_OR_3_InRow(vector<vector<char>>& board, char& maximaler, char& minimaler);
int EvalBoard(vector<vector<char>>& board, char& maximaler, char& minimaler);
void GetAllMoves(vector<vector<char>>& board, vector<vector<bool>>& moves);
char GetWinner(vector<vector<char>>& board);
int FindBestMove(vector<vector<char>> board, char turn, int depth, int& alpha, int& beta, char& maximaler, char& minimaler, int move_x, int move_y);

map<vector<vector<char>>, int> ALLBOARDS;

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

int FindBestMove(vector<vector<char>> board, char turn, int depth, int& alpha, int& beta, char& maximaler, char& minimaler,
	int move_x, int move_y)
{
	if (depth == 0)
	{
		return EvalBoard(board, maximaler, minimaler);
	}

	char winner = GetWinner(board);
	if (winner != '0')
	{
		return (winner = maximaler) ? INT_MAX : INT_MIN;
	}

	board[move_x][move_y] = (turn == minimaler) ? maximaler : minimaler;

	//skipping already considered boards:
	if (ALLBOARDS.find(board) != ALLBOARDS.end())
	{
		return ALLBOARDS[board];
	}

	int bestscore = (turn == maximaler) ? INT_MIN : INT_MAX;

	vector<vector<bool>> all_moves;
	GetAllMoves(board, all_moves);

	int eval;

	int seven_minus_i;
	int seven_plus_i;
	int seven_minus_j;
	int seven_plus_j;

	// Finding for maximaler
	if (turn == maximaler)
	{
		for (int i = 0; i <= 7; i++)
		{
			seven_minus_i = 7 - i;
			seven_plus_i = 7 + i;
			for (int j = 0; j <= 7; j++)
			{
				seven_minus_j = 7 - j;
				seven_plus_j = 7 + j;
				if (all_moves[seven_minus_j][seven_minus_i])
				{
					eval = FindBestMove(board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, seven_minus_j, seven_minus_i);
					bestscore = max(eval, bestscore);
					alpha = max(eval, alpha);
					if (beta <= alpha)
					{
						ALLBOARDS[board] = bestscore;
						return bestscore;
					}
				}if (j != 0 && i != 0)
				{
					if (all_moves[seven_plus_j][seven_minus_i])
					{
						eval = FindBestMove(board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, seven_plus_j, seven_minus_i);
						bestscore = max(eval, bestscore);
						alpha = max(eval, alpha);
						if (beta <= alpha)
						{
							ALLBOARDS[board] = bestscore;
							return bestscore;
						}
					}if (all_moves[seven_minus_j][seven_plus_i])
					{
						eval = FindBestMove(board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, seven_minus_j, seven_plus_i);
						bestscore = max(eval, bestscore);
						alpha = max(eval, alpha);
						if (beta <= alpha)
						{
							ALLBOARDS[board] = bestscore;
							return bestscore;
						}
					}if (all_moves[seven_plus_j][seven_plus_i])
					{
						eval = FindBestMove(board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, seven_plus_j, seven_plus_i);
						bestscore = max(eval, bestscore);
						alpha = max(eval, alpha);
						if (beta <= alpha)
						{
							ALLBOARDS[board] = bestscore;
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
		for (int i = 0; i <= 7; i++)
		{
			seven_minus_i = 7 - i;
			seven_plus_i = 7 + i;
			for (int j = 0; j <= 7; j++)
			{
				seven_minus_j = 7 - j;
				seven_plus_j = 7 + j;
				if (all_moves[seven_minus_j][seven_minus_i])
				{
					eval = FindBestMove(board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, seven_minus_j, seven_minus_i);
					bestscore = min(eval, bestscore);
					beta = min(eval, beta);
					if (beta <= alpha)
					{
						ALLBOARDS[board] = bestscore;
						return bestscore;
					}
				}if (j != 0 && i != 0)
				{
					if (all_moves[seven_plus_j][seven_minus_i])
					{
						eval = FindBestMove(board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, seven_plus_j, seven_minus_i);
						bestscore = min(eval, bestscore);
						beta = min(eval, beta);
						if (beta <= alpha)
						{
							ALLBOARDS[board] = bestscore;
							return bestscore;
						}
					}if (all_moves[seven_plus_j][seven_plus_i])
					{
						eval = FindBestMove(board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, seven_plus_j, seven_plus_i);
						bestscore = min(eval, bestscore);
						beta = min(eval, beta);
						if (beta <= alpha)
						{
							ALLBOARDS[board] = bestscore;
							return bestscore;
						}
					} if (all_moves[seven_minus_j][seven_plus_i])
					{
						eval = FindBestMove(board, minimaler, depth - 1, alpha, beta, maximaler, minimaler, seven_minus_j, seven_plus_i);
						bestscore = min(eval, bestscore);
						beta = min(eval, beta);
						if (beta <= alpha)
						{
							ALLBOARDS[board] = bestscore;
							return bestscore;
						}
					}
				}
			}
		}
	}
	ALLBOARDS[board] = bestscore;
	return bestscore;
}

void FindBestScoreInBoardAndReplaceBestIfBetter(bool if_move_possible, int& BestInd, int& BestScore, int& score, vector<vector<char>> board, char turn, int depth, int& alpha, int& beta,
	char maximaler, char minimaler, int move_x, int move_y)
{
	if (if_move_possible)
	{
		score = FindBestMove(board, turn, depth, alpha, beta, maximaler, minimaler, move_x, move_y);

		if (score > BestScore)
		{
			BestScore = score;
			BestInd = (15 * move_x) + move_y;
		}
	}
}

int GetBestMove(string& str_board, char turn, int depth, char maximaler, char minimaler)    //function that i will call from python
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
	int temp = 0;
	int BestInd = 0;

	int alpha = INT_MIN;
	int beta = INT_MAX;

	int score1 = 0, score2 = 0, score3 = 0, score4 = 0;

	int seven_minus_i;
	int seven_plus_i;
	int seven_minus_j;
	int seven_plus_j;

	for (int i = 0; i <= 7; i++)
	{
		seven_minus_i = 7 - i;
		seven_plus_i = 7 + i;
		for (int j = 0; j <= 7; j++)
		{
			cout << i << " " << j << endl;

			seven_minus_j = 7 - j;
			seven_plus_j = 7 + 1;

			thread* thread_1 = new thread(FindBestScoreInBoardAndReplaceBestIfBetter, possible_moves[seven_minus_j][seven_minus_i], ref(BestInd), ref(bestScore), ref(score1), board, AI->Opponent_character, depth - 1, ref(alpha), ref(beta), maximaler, minimaler, seven_minus_j, seven_minus_i);
			thread* thread_2 = new thread(FindBestScoreInBoardAndReplaceBestIfBetter, possible_moves[seven_plus_j][seven_plus_i], ref(BestInd), ref(bestScore), ref(score2), board, AI->Opponent_character, depth - 1, ref(alpha), ref(beta), maximaler, minimaler, seven_plus_j, seven_plus_i);
			thread* thread_3 = new thread(FindBestScoreInBoardAndReplaceBestIfBetter, possible_moves[seven_plus_j][seven_minus_i], ref(BestInd), ref(bestScore), ref(score3), board, AI->Opponent_character, depth - 1, ref(alpha), ref(beta), maximaler, minimaler, seven_plus_j, seven_minus_i);
			thread* thread_4 = new thread(FindBestScoreInBoardAndReplaceBestIfBetter, possible_moves[seven_minus_j][seven_plus_i], ref(BestInd), ref(bestScore), ref(score4), board, AI->Opponent_character, depth - 1, ref(alpha), ref(beta), maximaler, minimaler, seven_minus_j, seven_plus_i);

			thread_1->join();
			thread_2->join();
			thread_3->join();
			thread_4->join();

			if (bestScore == INT_MAX) return BestInd;
		}
	}
	return BestInd;
}

char GetWinner(vector<vector<char>>& board)
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
//return 15x15 board filled with bool. If field is true then its valid move
void GetAllMoves(vector<vector<char>>& board, vector<vector<bool>>& moves)
{
	//vector<vector<bool>> moves;
	for (int i = 0; i <= 14; i++)
	{
		vector<bool> empty_vec;
		moves.push_back(empty_vec);
		for (int j = 0; j <= 14; j++)
		{
			if (board[i][j] == '0' &&
				((i <= 13 && board[i + 1][j] != '0') || (i >= 1 && board[i - 1][j] != '0')
					|| (i <= 13 && j <= 13 && board[i + 1][j + 1] != '0') || (i >= 1 && j >= 1 && board[i - 1][j - 1] != '0')
					|| (i >= 1 && j <= 13 && board[i - 1][j + 1] != '0') || (i <= 13 && j >= 1 && board[i + 1][j - 1] != '0')
					|| (j <= 13 && board[i][j + 1] != '0') || (j >= 1 && board[i][j - 1] != '0')))
				moves[i].push_back(true);
			else
				moves[i].push_back(false);
		}
	}

}

//Evalueate the board
int EvalBoard(vector<vector<char>>& board, char& maximaler, char& minimaler)
{
	switch (GetWinner(board))
	{
	case 'X':
		return INT_MAX;
	case 'O':
		return INT_MIN;
	default:
		return GetAmountOf_4_OR_3_InRow(board, maximaler, minimaler);
	}
}

int GetAmountOf_4_OR_3_InRow(vector<vector<char>>& board, char& maximaler, char& minimaler) //AI +, player -
{
	int plus_score = 0;
	int minus_score = 0;
	int amount_of_maximaler_temp;
	int i_minus_sth[4];
	int j_minus_sth[4];
	for (int i = 0; i <= 14 - 0; i++)
	{
		i_minus_sth[3] = i - 4;
		i_minus_sth[2] = i - 3;
		i_minus_sth[1] = i - 2;
		i_minus_sth[0] = i - 1;
		for (int j = 0; j <= 14 - 0; j++)
		{
			amount_of_maximaler_temp = 1;
			if (board[i][j] == maximaler)
			{
				j_minus_sth[3] = j - 4;
				j_minus_sth[2] = j - 3;
				j_minus_sth[1] = j - 2;
				j_minus_sth[0] = j - 1;
				// Checking column i think
				if (i >= 4)
				{
					if (!(board[i_minus_sth[2]][j] == minimaler
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

						if (amount_of_maximaler_temp == 4)
						{
							plus_score += 2;
						}

					}
					amount_of_maximaler_temp = 1;
					if (!(board[i_minus_sth[1]][j] == minimaler || board[i_minus_sth[0]][j] == minimaler))
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

						if (amount_of_maximaler_temp == 3)
						{
							plus_score += 1;
						}
					}
					amount_of_maximaler_temp = 1;
					//checking diagnals from bottom left to upper right
					if (j >= 4)
					{
						if (!(board[i_minus_sth[2]][j_minus_sth[2]] == minimaler
							|| board[i_minus_sth[1]][j_minus_sth[1]] == minimaler || board[i_minus_sth[0]][j_minus_sth[0]] == minimaler))
						{
							if (board[i][j] == board[i_minus_sth[0]][j_minus_sth[0]])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[1]][j_minus_sth[1]])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[2]][j_minus_sth[2]])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[3]][j_minus_sth[3]])
							{
								amount_of_maximaler_temp++;
							};

							if (amount_of_maximaler_temp == 4)
							{
								plus_score += 2;
							}
						}
						amount_of_maximaler_temp = 1;
						if (!(board[i_minus_sth[1]][j_minus_sth[1]] == minimaler || board[i_minus_sth[0]][j_minus_sth[0]] == minimaler))
						{
							if (board[i][j] == board[i_minus_sth[0]][j_minus_sth[0]])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[1]][j_minus_sth[1]])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[2]][j_minus_sth[2]])
							{
								amount_of_maximaler_temp++;
							}

							if (amount_of_maximaler_temp == 3)
							{
								plus_score += 1;
							}
						}
					}
					//checking diagnals from bottom left to upper right     
					if (j <= 10)
					{
						if (!(board[i_minus_sth[2]][j + 3] == minimaler
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

							if (amount_of_maximaler_temp == 4)
							{
								plus_score += 2;
							}

						}
						amount_of_maximaler_temp = 1;
						if (!(board[i_minus_sth[1]][j + 2] == minimaler || board[i_minus_sth[0]][j + 1] == minimaler))
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

							if (amount_of_maximaler_temp == 3)
							{
								plus_score += 1;
							}
						}
					}
				}
				amount_of_maximaler_temp = 1;
				if (j >= 4)
				{
					//checking row i think
					if (!(board[i][j - 3] == minimaler
						|| board[i][j_minus_sth[1]] == minimaler || board[i][j_minus_sth[0]] == minimaler))
					{
						if (board[i][j] == board[i][j_minus_sth[0]])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i][j_minus_sth[1]])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i][j_minus_sth[2]])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i][j_minus_sth[3]])
						{
							amount_of_maximaler_temp++;
						}

						if (amount_of_maximaler_temp == 4)
						{
							plus_score += 2;
						}

					}
					amount_of_maximaler_temp = 1;
					if (!(board[i][j_minus_sth[1]] == minimaler || board[i][j_minus_sth[0]] == minimaler))
					{
						if (board[i][j] == board[i][j_minus_sth[0]])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i][j_minus_sth[1]])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i][j_minus_sth[2]])
						{
							amount_of_maximaler_temp++;
						}

						if (amount_of_maximaler_temp == 3)
						{
							plus_score += 1;
						}
					}
				}
			}
			else if (board[i][j] == minimaler)
			{
				j_minus_sth[3] = j - 4;
				j_minus_sth[2] = j - 3;
				j_minus_sth[1] = j - 2;
				j_minus_sth[0] = j - 1;
				if (i >= 4)
				{
					// Checking column
					if (!(board[i_minus_sth[2]][j] == maximaler
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

						if (amount_of_maximaler_temp == 4)
						{
							minus_score -= 2;
						}
					}
					amount_of_maximaler_temp = 1;
					if (!(board[i_minus_sth[1]][j] == maximaler || board[i_minus_sth[0]][j] == maximaler))
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

						if (amount_of_maximaler_temp == 3)
						{
							minus_score -= 1;
						}
					}

					amount_of_maximaler_temp = 1;
					if (j <= 10)
					{
						//checking diagnals from bottom left to upper right     
						if (!(board[i_minus_sth[2]][j + 3] == maximaler
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

							if (amount_of_maximaler_temp == 4)
							{
								minus_score -= 2;
							}

						}
						amount_of_maximaler_temp = 1;
						if (!(board[i_minus_sth[1]][j + 2] == maximaler || board[i_minus_sth[0]][j + 1] == maximaler))
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

							if (amount_of_maximaler_temp == 3)
							{
								minus_score -= 1;
							}
						}
					}

					if (j >= 4)
					{
						//checking diagnals from bottom left to upper right
						if (!(board[i_minus_sth[2]][j_minus_sth[2]] == maximaler
							|| board[i_minus_sth[1]][j_minus_sth[1]] == maximaler || board[i_minus_sth[0]][j_minus_sth[0]] == maximaler))
						{
							if (board[i][j] == board[i_minus_sth[0]][j_minus_sth[0]])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[1]][j_minus_sth[1]])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[2]][j_minus_sth[2]])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[3]][j_minus_sth[3]])
							{
								amount_of_maximaler_temp++;
							};

							if (amount_of_maximaler_temp == 4)
							{
								minus_score -= 2;
							}

						}
						amount_of_maximaler_temp = 1;
						if (!(board[i_minus_sth[1]][j_minus_sth[1]] == maximaler || board[i_minus_sth[0]][j_minus_sth[0]] == maximaler))
						{
							if (board[i][j] == board[i_minus_sth[0]][j_minus_sth[0]])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[1]][j_minus_sth[1]])
							{
								amount_of_maximaler_temp++;
							}
							if (board[i][j] == board[i_minus_sth[2]][j_minus_sth[2]])
							{
								amount_of_maximaler_temp++;
							}


							if (amount_of_maximaler_temp == 3)
							{
								minus_score -= 1;
							}
						}

					}


				}
				amount_of_maximaler_temp = 1;
				if (j >= 4)
				{
					//checking row
					if (!(board[i][j_minus_sth[2]] == maximaler
						|| board[i][j_minus_sth[1]] == maximaler || board[i][j_minus_sth[0]] == maximaler))
					{
						if (board[i][j] == board[i][j_minus_sth[0]])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i][j_minus_sth[1]])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i][j_minus_sth[2]])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i][j_minus_sth[3]])
						{
							amount_of_maximaler_temp++;
						};

						if (amount_of_maximaler_temp == 4)
						{
							minus_score -= 2;
						}

					}
					amount_of_maximaler_temp = 1;
					if (!(board[i][j_minus_sth[1]] == maximaler || board[i][j_minus_sth[0]] == maximaler))
					{
						if (board[i][j] == board[i][j_minus_sth[0]])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i][j_minus_sth[1]])
						{
							amount_of_maximaler_temp++;
						}
						if (board[i][j] == board[i][j_minus_sth[2]])
						{
							amount_of_maximaler_temp++;
						}

						if (amount_of_maximaler_temp == 3)
						{
							minus_score -= 1;
						}
					}
				}
				if (minus_score < -5) return INT_MIN;   //bc thats mean that opponent has a lot of possibilities
				amount_of_maximaler_temp = 1;
			}
		}
	}
	return plus_score + minus_score;
}

int main()
{
	bool making_data = false;
	int depth = 1;
	int left_x_subtstractor = 0, right_x_subtstractor = 0, left_y_subtstractor = 0, right_y_subtstractor = 0;
	string str_board;

	// Add loop HERE to making data, that will create board and look for best move

	if (!making_data)
	{
		// loading data from board.txt
		fstream board_file;
		board_file.open("board.txt");
		while (!board_file.eof())
		{
			board_file >> str_board >> depth; //>> left_x_subtstractor >> right_x_subtstractor >> left_y_subtstractor >> right_y_subtstractor;
		}
		board_file.close();
	}

	str_board[112] = 'O';

	// LOKONG FOR SAVED  BOARD HERE

	// if board is empty, go middle, idk if that if work XDDD
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
	/*
	str_board[98] = 'X';
	str_board[99] = 'O';
	str_board[100] = 'X';
	str_board[101] = 'X';
	str_board[102] = 'X';
	str_board[103] = 'O';
	str_board[117] = 'X';
	str_board[131] = 'O';
	str_board[145] = 'O';
	str_board[163] = 'O';
	str_board[178] = 'X';
	str_board[193] = 'X';
	str_board[208] = 'O';
	*/

	//converting str 15x15 board to vectors of vector  of chars
	vector<vector<char>> board;
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

	/// FINDING BEST MOVE
	//str_board[97] = 'X';

	const clock_t begin_time = clock();
	int move = GetBestMove(str_board, 'X', depth, 'X', 'O');
	cout << "MOVE: " << move << endl;
	str_board[move] = 'X';
	cout << "IT TOOK: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

	//move = GetBestMove(str_board, 'X', depth, 'X', 'O', left_x_subtstractor, right_x_subtstractor, left_y_subtstractor, right_y_subtstractor);
	//cout << "MOVE: " << move << endl;
	//str_board[move] = 'X';

	// Saving temp best move
	fstream return_file;
	return_file.open("string_index_return.txt", ios::out);
	return_file << move;
	return_file.close();

	//CREATING DATA
	fstream calculated_moves;
	calculated_moves.open("calculated_moves.txt", ios::out);
	calculated_moves << (string)str_board << " ; " << move << endl;
	calculated_moves.close();

	//Checking eval
	//char x = 'X';
	//char o = 'O';
	//cout << "BOARD EVAL: " << EvalBoard(board, x, o, left_x_subtstractor, right_x_subtstractor, left_y_subtstractor, right_y_subtstractor) << endl;

	board.clear();

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
	vector<vector<bool>> moves;
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
			else
				cout << "\033[0m" << board[i][j] << " ";

		}
		cout << "\033[0m" << endl;
	}

	exit(0);
}

/// OLD MAIN WITH BOARD SHOWING ///
/// 
/*
int main()
{

fstream board_file, return_file;
board_file.open("board.txt");
return_file.open("string_index_return.txt", ios::out);
return_file.open("calculated_moves.csv", ios::out);
string str_board;
while (!board_file.eof())
{
	board_file >> str_board;
}
board_file.close();

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

//cout << endl; cout << endl; cout << endl; cout << endl; cout << endl;

/// FINDING BEST
const clock_t begin_time = clock();
int move = GetBestMove(str_board, 'X', 3, 'X', 'O', 3, 3);
cout << "MOVE: " << move << endl;

cout << "IT TOOK: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
//return_file.clear();
return_file << move;
return_file.close();


//str_board[move] = 'X';
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



//exit(0);
}
*/
