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
	Game(Vector2 initPosition, double size);
	~Game();
	
	virtual void Init() = 0;
	//void SetUpNeighbours();
	
	virtual void Render(SDL_Renderer* renderer) = 0;
	
	virtual void Update() = 0;
	virtual void HandleEvents(SDL_Event& event)  = 0;
	virtual Owner GameOver() = 0;
	
	void ChangePlayer();
	void UpdatePlayerScore(Owner player, int scoreChange);
	
	int GetCurrentPlayerID();
	
	//void ProcessInput(Vector2 position);

protected:
	//void TakePositionOver(Vector2 position, Owner owner);

	//std::map<Vector2, Field*> fieldsMap;
	Vector2 position;
	double size;
	
	//std::vector<Vector2> inputPositions;
	int currentPlayerID;
	//std::map<Vector2, std::vector<Vector2>> neighbourhood;
	std::array<int, 2> score;
};

#endif //GAME_H