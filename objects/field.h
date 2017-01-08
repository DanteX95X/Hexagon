#ifndef FIELD_H
#define FIELD_H
#include <vector>
#include "actor.h"
#include "game.h"

class Game;

enum class Owner
{
	NONE = -1,
	PLAYER = 0,
	OPPONENT = 1,
};

class Field : public Actor
{
public:
	Field(Game* initGame, Vector2 initAxial, Vector2 position, float size, std::string texturePath, Owner initOwner = Owner::NONE);
	
	void HandleEvents(SDL_Event& event) override;
	void Update() override;
	void Render(SDL_Renderer* renderer) override;
	
	Owner GetOwner();
	void SetOwner(Owner newOwner);
	
	Vector2 GetAxial();
	
private:
	Vector2 axial;
	Owner owner;
	
	SDL_Texture* playerPawn;
	SDL_Texture* opponentPawn;
	
	Game* game;
};


#endif