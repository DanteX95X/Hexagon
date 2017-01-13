#ifndef HEXAGON_GAME_H
#define HEXAGON_GAME_H

#include "game.h"
#include "field.h"

class Field;

class HexagonGame : public Game
{
	public:
	HexagonGame(Vector2 initPosition, double size);
	~HexagonGame();
	
	void Init();
	void SetUpNeighbours();
	
	virtual void Render(SDL_Renderer* renderer) override;
	
	virtual void Update() override;
	virtual void HandleEvents(SDL_Event& event)  override;
	
	virtual Owner GameOver();
	
	void ProcessInput(Vector2 position);
	
	std::map<Vector2, Field*>& GetFieldsMap();
	std::map<Vector2, std::vector<Vector2>>& GetNeighbourhood();

private:
	void TakePositionOver(Vector2 position, Owner owner);


	std::map<Vector2, Field*> fieldsMap;
	
	std::vector<Vector2> inputPositions;
	std::map<Vector2, std::vector<Vector2>> neighbourhood;
};

#endif //HEXAGON_GAME_H