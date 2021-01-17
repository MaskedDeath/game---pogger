#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Car
{
private:
	int ylevel;
	float speed;
	float timer;
	float timerMax;
	bool reverse;

	Sprite sprite;

	RectangleShape& arena;

	void initSprite(Texture& texture);
	void initVariables(int type, float timerStart, RectangleShape& arena);

	void updateTimer();
	void move();
	void respawn();
public:
	Car(int type, float timerStart, RectangleShape& arena, Texture& texture);
	~Car();

	Sprite* getSprite();

	void update();
	void render(RenderTarget& window);
};