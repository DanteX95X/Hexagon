#ifndef HEXAGON_MOVE_H
#define HEXAGON_MOVE_H

#include "move.h"
#include "../objects/hexagon_game.h"


class HexagonMove : public Move
{
public:
	HexagonMove(Vector2 initSource, Vector2 initDestination);
	
	bool MakeAMove(Game* currentGame) override;
	
private:
	void TakePositionOver(HexagonGame* game, Vector2 position, Owner owner);

	Vector2 sourcePosition;
	Vector2 destinationPosition;
};


#endif //HEXAGON_MOVE_H