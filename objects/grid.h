#ifndef GRID_H
#define GRID_H
#include "field.h"
#include "../window/window.h"
#include <map>

class Grid: public Object
{
public:
	Grid(Vector2 initPosition, double size);
	
	void init();
	void render(Window& window);
	
	virtual void Update() override;
	
private:
	std::vector< Field > fields;
	std::map<std::pair<int, int>, Field> fieldsMap;
	Vector2 position;
	double size;
};

#endif