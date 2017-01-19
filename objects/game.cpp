#include "game.h"
#include "../utilities/hex.h"

Game::Game(Vector2 initPosition, double initSize, std::array<bool, 2> initIsAI)
	: Actor(initPosition, Vector2(0, 0)), position{initPosition}, size{initSize}, currentPlayerID{0}, score({0,0}), isAI(initIsAI)
{
};

Game::~Game()
{
}

void Game::ChangePlayer()
{
	currentPlayerID = (currentPlayerID + 1) % 2;
	std::cout << score[0] << " " << score[1] << "\n";
}

void Game::UpdatePlayerScore(Owner player, int scoreChange)
{
	score[static_cast<int>(player)] += scoreChange;
}

int Game::GetCurrentPlayerID() { return currentPlayerID; }