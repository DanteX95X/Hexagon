#ifndef MOVE_H
#define MOVE_H

#include "../objects/game.h"

class Move
{
public:
	Move();
	virtual ~Move();
	
	virtual bool MakeAMove(Game* currentGame) = 0;
};

#endif //MOVE_H