#include <ics46/factory/DynamicFactory.hpp>
#include "MyOthelloAI.hpp"
#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <memory>

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, mscha1::MyOthelloAI, "How I Met Your Othello (Required)")

std::pair<int, int> mscha1::MyOthelloAI::chooseMove(const OthelloGameState& state)
{
	std::pair<int,int> move;

	bool black = state.isBlackTurn();
	bool white = state.isWhiteTurn();
	int width = state.board().width();
	int height = state.board().height();
	//std::cout << "INITIAL TILES: " << std::endl;
	//std::cout << "Black: " << black << std::endl;
	//std::cout << "White: " << white << std::endl;

	std::vector<std::pair<int,int>> valid_moves = getValidMoves(state);

	std::vector<int> move_evals;
	for (auto move : valid_moves)
	{
		std::unique_ptr<OthelloGameState> clone_board = state.clone();
		clone_board->makeMove(move.first, move.second);

	//	std::cout << "Make move: " << valid_moves[i].first << ", " 
	//		<< valid_moves[i].second << std::endl;

		int s = searchMove(clone_board, 4, black, white);

		if (move.first == 0 || move.first == width - 1)
			
		{
			if (move.second == 0 || move.second == height - 1)
			{
				int markup = width*height/8;
				s += markup;
			}
		} 

		else if (move.first <= 1 || move.first >= width-2)
		{
			if (move.second <= 1 || move.second >= height - 2)
			{
				int markup = width*height/16;
				s -= markup;
			}
		}

		move_evals.push_back(s);
	}

	int best_eval = move_evals[0];
	std::pair<int,int> best_move = valid_moves[0];
	int i;
	for (i = 1; i < move_evals.size(); ++i)
	{
		if (move_evals[i] > best_eval)
		{
			best_eval = move_evals[i];
			best_move = valid_moves[i];
		}
	}

	//std::cout << "Best move: " << best_move.first << ", " << best_move.second
	//	<< std::endl;

	return best_move;	

}

int mscha1::MyOthelloAI::searchMove(std::unique_ptr<OthelloGameState>& s, 
	int depth, bool black, bool white)
{

	if (depth == 0)
	{
		return evaluateMove(s, black, white);
	}
	else if (s->isBlackTurn() == black || s->isWhiteTurn() == white)
	{
	//	std::cout << "My turn: ";
	//	std::cout << "Black: " << black << " ";
	//	std::cout << "White: " << white << std::endl;
		std::vector<std::pair<int,int>> possible_moves = getPossibleMoves(s);
		int max_num = -1000000;
		for (auto move : possible_moves)
		{
			std::unique_ptr<OthelloGameState> clone_game = s->clone();
			clone_game->makeMove(move.first, move.second);
			int n = searchMove(clone_game, depth-1, black, white);

			if (n > max_num)
			{
				max_num = n;
			}
		}
		return max_num;
	}
	else
	{
	//	std::cout << "Opponent turn: ";
	//	std::cout << "Black: " << black << " ";
	//	std::cout << "White: " << white << std::endl;
		std::vector<std::pair<int,int>> possible_moves = getPossibleMoves(s);
		int min_num = 1000000;
		for (auto move : possible_moves)
		{
			std::unique_ptr<OthelloGameState> clone_game = s->clone();
			clone_game->makeMove(move.first, move.second);
			int n = searchMove(clone_game, depth-1, black, white);

			if (n < min_num)
			{
				min_num = n;
			}
		}
		return min_num;
	}

}



std::vector<std::pair<int,int>> mscha1::MyOthelloAI::getValidMoves(
	const OthelloGameState& s)
{
	int width = s.board().width();
	int height = s.board().height();

	std::vector<std::pair<int,int>> valid_moves;

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			if (s.isValidMove(x, y))
			{
				std::pair location(x, y);
				valid_moves.push_back(location);
			}
		}
	}
	return valid_moves;
}

std::vector<std::pair<int,int>> mscha1::MyOthelloAI::getPossibleMoves(
	std::unique_ptr<OthelloGameState>& s)
{
	int width = s->board().width();
	int height = s->board().height();

	std::vector<std::pair<int,int>> possible_moves;

	for (int x = 0; x < width; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			if (s->isValidMove(x, y))
			{
				std::pair location(x,y);
				possible_moves.push_back(location);
			}
		}
	}
	return possible_moves;
}

int mscha1::MyOthelloAI::evaluateMove(std::unique_ptr<OthelloGameState>& s,
	bool black, bool white)
{
	int score;
	if (black == 1)
	{
		score = s->blackScore() - s->whiteScore();

		return score;
	}
	else
	{
		score = s->whiteScore() - s->blackScore();

		return score;
	}
}