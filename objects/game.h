#ifndef GAME_H
#define GAME_H
#include "../window/window.h"
#include <map>
#include <iostream>
#include <array>
#include "actor.h"
#include <memory>
#include <vector>
#include "../utilities/move.h"


enum class Owner
{
	NONE = -1,
	PLAYER = 0,
	OPPONENT = 1,
	DRAW = 2,
};

class Move;

class Game: public Actor
{
public:
	Game(Vector2 initPosition, double size, Uint32 initThinkingTime, std::array<bool, 2> initIsAI);
	Game(const Game& another);
	virtual ~Game();
	
	virtual void Init() = 0;

	virtual void Render(SDL_Renderer* renderer) = 0;
	
	virtual void Update() = 0;
	virtual void HandleEvents(SDL_Event& event)  = 0;
	virtual Owner GameOver() = 0;
	virtual std::vector<std::shared_ptr<Move>> GenerateMoves() = 0;
	virtual std::shared_ptr<Game> Clone() = 0;
	virtual int EvaluateGame() = 0;
	
	void ChangePlayer();
	void UpdatePlayerScore(Owner player, int scoreChange);
	
	int GetCurrentPlayerID();

protected:
	Vector2 position;
	double size;
	
	int currentPlayerID;
	std::array<int, 2> score;
	std::array<bool, 2> isAI;
	
	Uint32 thinkingTime;
};

#endif //GAME_H