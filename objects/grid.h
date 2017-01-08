#ifndef GRID_H
#define GRID_H
#include "field.h"
#include "../window/window.h"
#include <map>
#include <unordered_map>
#include <boost/functional/hash.hpp>

class Grid: public Object
{
public:
	Grid(Vector2 initPosition, double size);
	~Grid();
	
	void Init();
	void Render(Window& window);
	
	virtual void Update() override;
	
	std::map<std::pair<int, int>, Field*>& GetFields();
	
private:
	std::map<std::pair<int, int>, Field*> fieldsMap;
	Vector2 position;
	double size;
};

#endif