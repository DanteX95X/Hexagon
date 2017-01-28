#include "hexagon_move.h"
#include "hex.h"

HexagonMove::HexagonMove(Vector2 initSource, Vector2 initDestination)
	: Move(), sourcePosition(initSource), destinationPosition{initDestination}
{	
}

bool HexagonMove::MakeAMove(Game* currentGame)
{
	HexagonGame* game = static_cast<HexagonGame*>(currentGame);
	std::map<Vector2, Field*>& fieldsMap = game->GetFieldsMap();
	
	Field* source = fieldsMap[sourcePosition];
	
	if( source->GetOwner() == Owner::NONE || static_cast<int>(source->GetOwner()) != game->GetCurrentPlayerID() )
	{
		return false;
	}
	
	unsigned int distance = Hex::Distance(sourcePosition, destinationPosition);
	Field* destination = fieldsMap[destinationPosition];
	
	if(destination->GetOwner() != Owner::NONE)
	{
		return false;
	}
	
	if( distance == 1 )
	{
		game->UpdatePlayerScore(source->GetOwner(), 1);
		TakePositionOver(game, destination->GetAxial(), source->GetOwner());
		return true;
		
	}
	else if( distance == 2 )
	{
		TakePositionOver(game, destination->GetAxial(), source->GetOwner());
		source->SetOwner(Owner::NONE);
		return true;
	}
	else
	{
		return false;
	}
	return true;
}

void HexagonMove::TakePositionOver(HexagonGame* game, Vector2 position, Owner owner)
{
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
			neighbour->SetOwner(owner);
		 }
	}
	
	game->ChangePlayer();
			
	
	
	//Owner winner = game->GameOver();
	//if( winner != Owner::NONE)
	//	std::cout << "Game Over! Winner: " << static_cast<int>(winner) << "\n";
}