#include "grid.h"

Grid::Grid(Vector2 initPosition, double initSize)
	: Object(initPosition, Vector2(initSize, initSize)), position{initPosition}, size{initSize} 
{
	Init();
};

Grid::~Grid()
{
	for( auto& field : fieldsMap )
	{
		delete field.second;
	}
}

void Grid::Init()
{

	int left = 0;
	int right = 5;
	for(int i = -4; i < 5; ++i)
	{
		for(int j = left; j < right; ++j)
		{
			if( ( i==-1 && j == 0 ) || ( i == 0 && j == 1 ) || ( i == 1 && j == -1 ) )
				continue;
				
			Owner fieldOwner = Owner::NONE;
			if( ( i == 4 && j == 0)  || ( i == 0 && j == -4)  || ( i == -4 && j == 4) )
				fieldOwner = Owner::PLAYER;
			else if( ( i == -4 && j == 0)  || ( i == 0 && j == 4)  || ( i == 4 && j == -4) )
				fieldOwner = Owner::OPPONENT;
			
			const double proportion = 0.485;
			double x =  position.x + size*proportion * 1.5 * static_cast<double>(j);
			double y  =  position.y + 1.73*size*proportion*static_cast<double>(i) + 1.73*size*proportion*0.5*static_cast<double>(j);
			
			Vector2 axial(static_cast<double>(j), static_cast<double>(i));
			Field* temporaryField = new Field(axial, {x,y},size, "crate.png", fieldOwner);
			std::pair<int, int> abstractCoordinates(j, i);
			//fieldsMap[abstractCoordinates] = temporaryField;
			fieldsMap.insert(std::pair<std::pair<int, int>, Field*>(abstractCoordinates, temporaryField));
		}
		
		if(i<0) --left;
		else --right;
		
	}

}


void Grid::Render(Window& window)
{
	/*for(typename std::map<std::pair<int, int>, Field>::iterator i = fieldsMap.begin(); i != fieldsMap.end(); ++i)
	{
		i->second.Render(window.GetRenderer());
	}*/
	
	for(auto& field : fieldsMap)
	{
		field.second->Render(window.GetRenderer());
	}
}

void Grid::Update()
{
}


std::map<std::pair<int, int>, Field*>& Grid::GetFields() { return fieldsMap; }