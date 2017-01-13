#include "hexagon_game.h"
#include "../utilities/hex.h"
#include "../utilities/hexagon_move.h"

HexagonGame::HexagonGame(Vector2 initPosition, double initSize)
	: Game(initPosition, initSize), inputPositions()
{
	Init();
};

HexagonGame::~HexagonGame()
{
	for( auto& field : fieldsMap )
	{
		delete field.second;
	}
}

void HexagonGame::Init()
{

	int left = 0;
	int right = 5;
	for(int i = -4; i < 5; ++i)
	{
		for(int j = left; j < right; ++j)
		{
			if( ( i==-1 && j == 0 ) || ( i == 0 && j == 1 ) || ( i == 1 && j == -1 ) )
				continue;
				
			Owner fieldOwner = Owner::NONE;
			if( ( i == 4 && j == 0)  || ( i == 0 && j == -4)  || ( i == -4 && j == 4) )
				fieldOwner = Owner::PLAYER;
			else if( ( i == -4 && j == 0)  || ( i == 0 && j == 4)  || ( i == 4 && j == -4) )
				fieldOwner = Owner::OPPONENT;
			
			const double proportion = 0.485;
			double x =  position.x + size*proportion * 1.5 * static_cast<double>(j);
			double y  =  position.y + 1.73*size*proportion*static_cast<double>(i) + 1.73*size*proportion*0.5*static_cast<double>(j);
			
			Vector2 axial(static_cast<double>(j), static_cast<double>(i));
			Field* temporaryField = new Field(this, axial, {x,y},size, "hex.png", fieldOwner);
			std::pair<int, int> abstractCoordinates(j, i);
			fieldsMap[axial] = temporaryField;
		}
		
		if(i<0) --left;
		else --right;
		
	}


	SetUpNeighbours();
	
	for(auto& ufo : neighbourhood)
	{
		std::cout << ufo.first;
		std::cout << "\t";
		for(Vector2 porno : ufo.second)
		{
			std::cout << porno;
			std::cout << " ";
		}
		std::cout << "\n";
	}
}


void HexagonGame::Render(SDL_Renderer* renderer)
{	
	for( auto& field : fieldsMap )
	{
		field.second->Render(renderer);
	}
}

void HexagonGame::Update()
{
}

void HexagonGame::HandleEvents(SDL_Event& event)
{
	for( auto& field : fieldsMap )
	{
		field.second->HandleEvents(event);
	}
}

void HexagonGame::ProcessInput(Vector2 position)
{
	inputPositions.push_back(position);
	Field* source = fieldsMap[inputPositions.front()];
	
	if( source->GetOwner() == Owner::NONE || static_cast<int>(source->GetOwner()) != currentPlayerID )
	{
		std::cout << "Empty!\n";
		inputPositions.clear();
		return;
	}
	
	if(inputPositions.size() == 2)
	{
		unsigned int distance = Hex::Distance(inputPositions.front(), inputPositions.back());
		Field* destination = fieldsMap[inputPositions.back()];
		
		if(destination->GetOwner() != Owner::NONE)
		{
			inputPositions.erase(inputPositions.begin());
			return;
		}
		
		if( distance == 1 )
		{
			++score[static_cast<int>(source->GetOwner())];
			//TakePositionOver(destination->GetAxial(), source->GetOwner());
			HexagonMove move(destination->GetAxial(), source->GetOwner());
			move.MakeAMove(this);
			inputPositions.clear();
			
		}
		else if( distance == 2 )
		{
			HexagonMove move(destination->GetAxial(), source->GetOwner());
			move.MakeAMove(this);
			inputPositions.clear();
			//TakePositionOver(destination->GetAxial(), source->GetOwner());
			source->SetOwner(Owner::NONE);
			
		}
		else
		{
			inputPositions.erase(inputPositions.begin());
		}
		

	}
}

void HexagonGame::SetUpNeighbours()
{
	for( auto& field : fieldsMap )
	{
		for( Vector2 displacement : Hex::displacements )
		{
			auto neighbour = fieldsMap.find(field.second->GetAxial() + displacement);
			if(neighbour != fieldsMap.end())
				neighbourhood[field.second->GetAxial()].push_back(field.second->GetAxial() + displacement);
		}
	}
}

void HexagonGame::TakePositionOver(Vector2 position, Owner owner)
{
	Field* field = fieldsMap[position];
	field->SetOwner(owner);
	
	for( Vector2 neighbourPosition : neighbourhood[position] )
	{
		 Field* neighbour = fieldsMap[neighbourPosition];
		 if( neighbour->GetOwner() != Owner::NONE && neighbour->GetOwner() != owner)
		 {
			 ++score[static_cast<int>(owner)];
			 --score[static_cast<int>(neighbour->GetOwner())];
			neighbour->SetOwner(owner);
		 }
	}
	
	inputPositions.clear();
	currentPlayerID = (currentPlayerID + 1) % 2;
			
	std::cout << score[0] << " " << score[1] << "\n";
	
	Owner winner = GameOver();
	if( winner != Owner::NONE)
		std::cout << "Game Over! Winner: " << static_cast<int>(winner) << "\n";
}

Owner HexagonGame::GameOver()
{
	if( score[1]  == 0 || (score[0] + score[1] == 58 && score[0] > score[1]) )
		return Owner::PLAYER;
	else if( score[0] == 0 || (score[0] + score[1] == 58 && score[0] < score[1]) )
		return Owner::OPPONENT;
	
	return Owner::NONE;
}

std::map<Vector2, Field*>& HexagonGame::GetFieldsMap() { return fieldsMap; }
std::map<Vector2, std::vector<Vector2>>& HexagonGame::GetNeighbourhood() { return neighbourhood; }