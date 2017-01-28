#include "hexagon_game.h"
#include "../utilities/hex.h"
#include "../utilities/hexagon_move.h"
#include <algorithm>
#include <memory>
#include <climits>
#include "../min_max/ai.h"

HexagonGame::HexagonGame(Vector2 initPosition, double initSize, Uint32 initThinkingTime, std::array<bool, 2> initIsAI)
	: Game(initPosition, initSize, initThinkingTime, initIsAI), mapSize{0}, inputPositions()
{
	Init();
}

HexagonGame::HexagonGame(const HexagonGame& another)
	: Game(another)
{
	for(auto& field : another.fieldsMap)
	{
		Field* newField = new Field(*field.second);
		newField->SetGame(this);
		fieldsMap[field.first] = newField;
	}
	mapSize = another.mapSize;
	neighbourhood = another.neighbourhood;
	inputPositions = another.inputPositions;
}


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

	mapSize = fieldsMap.size();
	std::cout << "MapSize = " << mapSize << '\n';
	SetUpNeighbours();
	
	for(auto& field : fieldsMap)
	{
		if(field.second->GetOwner() != Owner::NONE)
			++score[static_cast<int>(field.second->GetOwner())];
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
	if( isAI[currentPlayerID] && GameOver() == Owner::NONE)
	{
		int level = 1;
		Uint32 startTime = SDL_GetTicks();
		
		std::pair<int, std::shared_ptr<Move>> bestMove(0, nullptr);
		do
		{
			bestMove = AI::AlphaBetaPruning(this, level, INT_MIN, INT_MAX, currentPlayerID == 0, nullptr);
			std::cout << "Best move " << bestMove.first << "\n";
			
			++level;
			if( (SDL_GetTicks() - startTime) / static_cast<double>(thinkingTime) > 0.5)
				break;
		}
		while(SDL_GetTicks() - startTime < thinkingTime);

		if(bestMove.second != nullptr)
			bestMove.second->MakeAMove(this);
		
	}
}

void HexagonGame::HandleEvents(SDL_Event& event)
{
	if( !isAI[currentPlayerID] )
	{
		for( auto& field : fieldsMap )
		{
			field.second->HandleEvents(event);
		}
	}
}

void HexagonGame::ProcessInput(Vector2 position)
{
	inputPositions.push_back(position);
	
	if(inputPositions.size() == 2)
	{
		HexagonMove move(inputPositions[0], inputPositions[1]);
		bool isMoveValid = move.MakeAMove(this);
		
		if(isMoveValid)
			inputPositions.clear();
		else
			inputPositions.erase(inputPositions.begin());

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

Owner HexagonGame::GameOver()
{
	if( score[1]  == 0 || (score[0] + score[1] ==  mapSize && score[0] > score[1]) )
		return Owner::PLAYER;
	else if( score[0] == 0 || (score[0] + score[1] == mapSize && score[0] < score[1]) )
		return Owner::OPPONENT;
		
	auto moves = GenerateMoves();
	if(moves.size() == 0)
		return static_cast<Owner>(1 - currentPlayerID);
	
	return Owner::NONE;
}

std::vector< std::shared_ptr<Move>> HexagonGame::GenerateMoves()
{
	std::map<Vector2, std::shared_ptr<Move> > moves;
	for(auto& field : fieldsMap)
	{
		if( field.second->GetOwner() == static_cast<Owner>(currentPlayerID))
		{
			for(Vector2 neighbourPosition : neighbourhood[field.first])
			{
				Field* neighbour = fieldsMap[neighbourPosition];
				if(neighbour->GetOwner() == Owner::NONE)
				{
					moves.insert({neighbourPosition, std::shared_ptr<Move> (new HexagonMove(field.first, neighbourPosition))} );
					for(Vector2 furtherNeighbourPosition : neighbourhood[neighbourPosition])
					{
						Field* furtherNeighbour = fieldsMap[furtherNeighbourPosition];
						if(furtherNeighbour->GetOwner() == Owner::NONE)
							moves.insert({furtherNeighbourPosition, std::shared_ptr<Move> (new HexagonMove(field.first, furtherNeighbourPosition))} );
					}
				}
			}
		}
	}
	
	std::vector<std::shared_ptr<Move>> allMoves;
	
	for(auto& move : moves)
		allMoves.push_back(move.second);
	
	return allMoves;
}

std::shared_ptr<Game> HexagonGame::Clone()
{
	return std::shared_ptr<Game>(new HexagonGame(*this));
}

int HexagonGame::EvaluateGame()
{
	return score[0] - score[1];
}

std::map<Vector2, Field*>& HexagonGame::GetFieldsMap() { return fieldsMap; }
std::map<Vector2, std::vector<Vector2>>& HexagonGame::GetNeighbourhood() { return neighbourhood; }