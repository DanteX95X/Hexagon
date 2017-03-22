#ifndef AI_H
#define AI_H

#include <climits>
#include <algorithm>
#include "../objects/game.h"

namespace AI
{
	std::pair<int, std::shared_ptr<Move>> AlphaBetaPruning(Game* state, int depth, int alpha, int beta, bool isMaximizing, std::shared_ptr<Move> lastMove, Uint32 timeLimit, Uint32 timePassed);
}

#endif //AI_H