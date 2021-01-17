#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Land
{
private:
	RectangleShape shape;
public:
	Land(int x, int y);
	~Land();

	Shape* getShape();
};

