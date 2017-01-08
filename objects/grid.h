#ifndef GRID_H
#define GRID_H
#include "field.h"
#include "../window/window.h"
#include <map>

class Grid: public Actor
{
public:
	Grid(Vector2 initPosition, double size);
	~Grid();
	
	void Init();
	virtual void Render(SDL_Renderer* renderer) override;
	
	virtual void Update() override;
	virtual void HandleEvents(SDL_Event& event)  override;
	
private:
	std::map<Vector2, Field*> fieldsMap;
	Vector2 position;
	double size;
};

#endif