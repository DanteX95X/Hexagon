#include "game.h"

Game::Game(Vector2 initPosition, double initSize)
	: Actor(initPosition, Vector2(initSize, initSize)), position{initPosition}, size{initSize} 
{
	Init();
};

Game::~Game()
{
	for( auto& field : fieldsMap )
	{
		delete field.second;
	}
}

void Game::Init()
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

}


void Game::Render(SDL_Renderer* renderer)
{	
	for( auto& field : fieldsMap )
	{
		field.second->Render(renderer);
	}
}

void Game::Update()
{
}

void Game::HandleEvents(SDL_Event& event)
{
	for( auto& field : fieldsMap )
	{
		field.second->HandleEvents(event);
	}
}