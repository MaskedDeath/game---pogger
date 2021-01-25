#include "Land.h"

Land::Land(int x, int y)
{
	this->shape = RectangleShape(Vector2f(48, 32));
	this->shape.setFillColor(Color::Transparent);
	this->shape.setPosition(x, y);
}

Land::~Land()
{
}

Shape* Land::getShape()
{
	return &this->shape;
}