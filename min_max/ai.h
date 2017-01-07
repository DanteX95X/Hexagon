#ifndef AI_H
#define AI_H

#include <climits>
#include <algorithm>
#include "vertex.h"

namespace AI
{
	int AlphaBetaPruning(Vertex* vertex, int depth, int alpha, int beta, bool isMaximizing);
}

#endif //AI_H