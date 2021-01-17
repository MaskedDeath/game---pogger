#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

enum direction { UP = -2, LEFT = -1, RIGHT = 1, DOWN = 2 };

class Frog
{
private:
	float speed;

	Vector2f start;

	Sprite sprite;
	Texture texture;

	void initSprite(Texture& texture);
	void initVariables(Vector2f start);
public:
	Frog(int x, int y, Texture& texture);
	~Frog();

	void move(int dir, RectangleShape& arena);
	void move(float amount, RectangleShape& arena);
	void respawn();

	Sprite* getSprite();

	void render(RenderTarget& window);
};

