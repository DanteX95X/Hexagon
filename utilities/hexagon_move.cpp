#include "hexagon_move.h"
#include "../objects/hexagon_game.h"

HexagonMove::HexagonMove(Vector2 initPosition, Owner initOwner)
	: Move(), position(initPosition), owner{initOwner}
{	
}

void HexagonMove::MakeAMove(Game* currentGame)
{
	HexagonGame* game = static_cast<HexagonGame*>(currentGame);
	std::map<Vector2, Field*>& fieldsMap = game->GetFieldsMap();
	std::map<Vector2, std::vector<Vector2>>& neighbourhood = game->GetNeighbourhood();
	
	Field* field = fieldsMap[position];
	field->SetOwner(owner);
	
	for( Vector2 neighbourPosition : neighbourhood[position] )
	{
		 Field* neighbour = fieldsMap[neighbourPosition];
		 if( neighbour->GetOwner() != Owner::NONE && neighbour->GetOwner() != owner)
		 {
			 game->UpdatePlayerScore(owner, 1);
			 game->UpdatePlayerScore(neighbour->GetOwner(), -1);
			 //++score[static_cast<int>(owner)];
			 //--score[static_cast<int>(neighbour->GetOwner())];
			neighbour->SetOwner(owner);
		 }
	}
	
	//currentPlayerID = (currentPlayerID + 1) % 2;
	game->ChangePlayer();
			
	
	
	Owner winner = game->GameOver();
	if( winner != Owner::NONE)
		std::cout << "Game Over! Winner: " << static_cast<int>(winner) << "\n";
}