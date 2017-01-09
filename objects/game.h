#ifndef GAME_H
#define GAME_H
#include "field.h"
#include "../window/window.h"
#include <map>
#include <iostream>
#include <array>

class Field;
enum class Owner;

class Game: public Actor
{
public:
	Game(Vector2 initPosition, double size);
	~Game();
	
	void Init();
	void SetUpNeighbours();
	
	virtual void Render(SDL_Renderer* renderer) override;
	
	virtual void Update() override;
	virtual void HandleEvents(SDL_Event& event)  override;
	
	void ProcessInput(Vector2 position);

private:
	void TakePositionOver(Vector2 position, Owner owner);
	Owner GameOver();

	std::map<Vector2, Field*> fieldsMap;
	Vector2 position;
	double size;
	
	std::vector<Vector2> inputPositions;
	int currentPlayerID;
	std::map<Vector2, std::vector<Vector2>> neighbourhood;
	std::array<int, 2> score;
};

#endif //GAME_H