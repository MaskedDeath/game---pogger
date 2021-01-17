#include "Frog.h"

Frog::Frog(int x, int y, Texture& texture)
{
	this->initSprite(texture);
	this->initVariables(Vector2f(x, y));
}

Frog::~Frog()
{
}

void Frog::move(int dir, RectangleShape& arena)
{
	int x = 0;
	int y = 0;
	switch (dir)
	{
	case -2:
		y = -1;
		x = 0;
		break;
	case 2:
		y = 1;
		x = 0;
		break;
	case -1:
		y = 0;
		x = -1;
		break;
	case 1:
		y = 0;
		x = 1;
		break;
	}

	this->sprite.move(Vector2f(x, y) * this->speed);
	if (!arena.getGlobalBounds().intersects(this->sprite.getGlobalBounds()))
	{
		this->move(-dir, arena);
	}
}

void Frog::move(float amount, RectangleShape& arena)
{
	this->sprite.move(Vector2f(amount, 0));
	if (!arena.getGlobalBounds().intersects(this->sprite.getGlobalBounds()))
	{
		this->sprite.move(Vector2f(-amount, 0));
	}
}

void Frog::respawn()
{
	this->sprite.setPosition(this->start);
}

Sprite* Frog::getSprite()
{
	return &this->sprite;
}

void Frog::initSprite(Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Frog::initVariables(Vector2f start)
{
	this->speed = 32.f;
	this->start = start;
	this->respawn();
}

void Frog::render(RenderTarget& window)
{
	window.draw(this->sprite);
}
