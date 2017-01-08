#ifndef GAME_H
#define GAME_H
#include "field.h"
#include "../window/window.h"
#include <map>
#include <iostream>

class Field;

class Game: public Actor
{
public:
	Game(Vector2 initPosition, double size);
	~Game();
	
	void Init();
	virtual void Render(SDL_Renderer* renderer) override;
	
	virtual void Update() override;
	virtual void HandleEvents(SDL_Event& event)  override;
	
	void ProcessInput(Vector2 position);
private:
	std::map<Vector2, Field*> fieldsMap;
	Vector2 position;
	double size;
	
	std::vector<Vector2> inputPositions;
};

#endif //GAME_H