#ifndef GAME_H
#define GAME_H
#include "../window/window.h"
#include <map>
#include <iostream>
#include <array>
#include "actor.h"


enum class Owner
{
	NONE = -1,
	PLAYER = 0,
	OPPONENT = 1,
};

class Game: public Actor
{
public:
	Game(Vector2 initPosition, double size, std::array<bool, 2> initIsAI);
	~Game();
	
	virtual void Init() = 0;

	virtual void Render(SDL_Renderer* renderer) = 0;
	
	virtual void Update() = 0;
	virtual void HandleEvents(SDL_Event& event)  = 0;
	virtual Owner GameOver() = 0;
	
	void ChangePlayer();
	void UpdatePlayerScore(Owner player, int scoreChange);
	
	int GetCurrentPlayerID();

protected:
	Vector2 position;
	double size;
	
	int currentPlayerID;
	std::array<int, 2> score;
	std::array<bool, 2> isAI;
};

#endif //GAME_H