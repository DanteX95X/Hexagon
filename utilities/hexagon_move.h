#ifndef HEXAGON_MOVE_H
#define HEXAGON_MOVE_H

#include "move.h"


class HexagonMove : public Move
{
public:
	HexagonMove(Vector2 initPosition, Owner initOwner);
	
	void MakeAMove(Game* currentGame) override;
	
private:
	Vector2 position;
	Owner owner;
};


#endif //HEXAGON_MOVE_H