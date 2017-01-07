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
			value = std::max(value, AlphaBetaPruning(child, depth-1, alpha, beta, false));
			alpha = std::max(value, alpha);
			if( beta <= alpha )
				break;
		}
	}
	else
	{
		value = INT_MAX;
		for( Vertex*& child : vertex->GetChildren() )
		{
			value = std::min(value, AlphaBetaPruning(child, depth - 1, alpha, beta, true));
			beta = std::min(value, beta);
			if( beta <= alpha )
				break;
		}
	}
	vertex->SetValue(value);
	return value;
}