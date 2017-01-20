#include "ai.h"

std::pair<int, std::shared_ptr<Move>> AI::AlphaBetaPruning(Game* state, int depth, int alpha, int beta, bool isMaximizing, std::shared_ptr<Move> lastMove)
{
	//std::cout << "Moves " << state->GenerateMoves().size() << "\n";
	if(depth == 0 || state->GameOver() != Owner::NONE )
		return {state->EvaluateGame(), lastMove};
	
	int value;
	std::shared_ptr<Move> bestMove;
	if( isMaximizing )
	{
		value = INT_MIN;
		for( auto move : state->GenerateMoves() )
		{
			std::shared_ptr<Game> child(state->Clone());
			move->MakeAMove(child.get());
			std::pair<int, std::shared_ptr<Move>> nextLevelValue = AlphaBetaPruning(child.get(), depth-1, alpha, beta, false, move);
			
			if(nextLevelValue.first > value)
			{
				value = nextLevelValue.first;
				bestMove = move;
			}
			alpha = std::max(alpha, value);
			if( beta <= alpha )
			{
				break;
			}
			//std::cout << "Maximizer value " << value << "\n";
			
		}
		return {value, bestMove};
	}
	else
	{
		value = INT_MAX;
		auto moves = state->GenerateMoves();
		//std::cout << "Size " << moves.size() << "\n";
		for( auto move : moves )
		{
			std::shared_ptr<Game> child(state->Clone());
			move->MakeAMove(child.get());
			std::pair<int, std::shared_ptr<Move>> nextLevelValue = AlphaBetaPruning(child.get(), depth - 1, alpha, beta, true, move);
			
			if(nextLevelValue.first < value)
			{
				value = nextLevelValue.first;
				bestMove = move;
			}
			beta = std::min(beta, value);
			if( beta <= alpha )
			{
				break;
			}
			//std::cout << "Minimizer value " << value << "\n";
			
		}
		return {value, bestMove};
	}
	return {value, bestMove};
}