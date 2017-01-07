#ifndef GRID_H
#define GRID_H
#include "field.h"
#include "window/window.h"

class Grid: public Object
{
public:
	Grid(Vector2 initPosition, Vector2 initSize)
	:Object(initPosition, initSize) 
	{
		position = initPosition;
	};
	
	void init();
	void render(Window& window);
	
	virtual void Update() override;
	
private:
	std::vector< Field*  > fields;
	Vector2 position;
};

#endif