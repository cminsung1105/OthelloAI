#ifndef MYOTHELLOAI_HPP
#define MYOTHELLOAI_HPP

#include "OthelloAI.hpp"
#include <utility>
#include <map>


namespace mscha1
{
	class MyOthelloAI : public OthelloAI
	{
	public:
		virtual std::pair<int,int> chooseMove(const OthelloGameState& state);
		int searchMove(std::unique_ptr<OthelloGameState>& s, 
			int depth, bool black, bool white);
		std::vector<std::pair<int,int>> getValidMoves(const OthelloGameState& s);
		std::vector<std::pair<int,int>> getPossibleMoves(
			std::unique_ptr<OthelloGameState>& s);
		int evaluateMove(std::unique_ptr<OthelloGameState>& s,
			bool black, bool white);
	};
}

#endif