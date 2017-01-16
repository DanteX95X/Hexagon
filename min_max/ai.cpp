#include "ai.h"

int AI::AlphaBetaPruning(Vertex* vertex, int depth, int alpha, int beta, bool isMaximizing)
{
	if(depth == 0 || vertex->GetChildren().size() == 0 )
		return vertex->GetValue();
	
	int value;
	if( isMaximizing )
	{
		value = INT_MIN;
		for( Vertex*& child : vertex->GetChildren() )
		{
			alpha = std::max(std::max(value, AlphaBetaPruning(child, depth-1, alpha, beta, false)), alpha);
			if( beta <= alpha )
			{
				value = beta;
				break;
			}
			else
				value = alpha;
		}
	}
	else
	{
		value = INT_MAX;
		for( Vertex*& child : vertex->GetChildren() )
		{
			//value = ;
			beta = std::min(std::min(value, AlphaBetaPruning(child, depth - 1, alpha, beta, true)), beta);
			if( beta <= alpha )
			{
				value = alpha;
				break;
			}
			else
				value = beta;
		}
	}
	vertex->SetValue(value);
	return value;
}