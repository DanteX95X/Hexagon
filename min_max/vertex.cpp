#include "vertex.h"
#include <iostream>

Vertex::Vertex(int initValue)
	: value{initValue}
{
	
}

Vertex::~Vertex()
{
	std::cout << "Destructor called\n";
	
	for(Vertex*& child : children)
		delete child;
}

void Vertex::AddChild(Vertex* child)
{
	children.push_back(child);
}

Vertex* Vertex::BuildTree(int childQuantity, int value)
{
	Vertex* vertex = new Vertex(value);
	
	for(int i = 0; i < childQuantity; ++i)
	{
		int newChildQuantity, newValue;
		std::cin >> newChildQuantity >> newValue;
		std::cout << newChildQuantity << " " << newValue << "\n";
		vertex->AddChild(BuildTree(newChildQuantity, newValue));
	}
	
	return vertex;
}

int Vertex::GetValue() { return value; }
std::vector<Vertex*>& Vertex::GetChildren() { return children; }