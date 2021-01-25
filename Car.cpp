#include "Car.h"

void Car::initSprite(Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Car::initVariables(int type, float timerStart, RectangleShape& arena)
{
	this->ylevel = type;
	switch (type)
	{
	case 1:
		this->timerMax = 180;
		this->speed = -6.f;
		this->reverse = true;
		break;
	case 2:
		this->timerMax = 480;
		this->speed = 2.f;
		this->reverse = false;
		break;
	case 3:
		this->timerMax = 160;
		this->speed = -4.f;
		this->reverse = true;
		break;
	case 4:
		this->timerMax = 180;
		this->speed = -15.f;
		this->reverse = true;
		break;
	case 5:
		this->timerMax = 240;
		this->speed = 9.f;
		this->reverse = false;
		break;
	}
	this->timer = timerStart;
}

void Car::updateTimer()
{
	this->timer += 1;
	if (this->timer >= this->timerMax)
	{
		this->timer = 0;
		this->respawn();
	}
}

void Car::move()
{
	this->sprite.move(speed, 0);
}

void Car::respawn()
{
	if (!this->reverse)
	{
		this->sprite.setPosition(this->arena.getGlobalBounds().left - this->sprite.getGlobalBounds().width, this->arena.getGlobalBounds().top + this->arena.getGlobalBounds().height - 32 * (1 + this->ylevel));
	}
	else
	{
		this->sprite.setPosition(this->arena.getGlobalBounds().left + this->arena.getGlobalBounds().width, this->arena.getGlobalBounds().top + this->arena.getGlobalBounds().height - 32 * (1 + this->ylevel));
	}
}

Car::Car(int type, float timerStart, RectangleShape& arena, Texture& texture):arena(arena)
{
	this->initVariables(type, timerStart, arena);
	this->initSprite(texture);
}

Car::~Car()
{
}

Sprite* Car::getSprite()
{
	return &this->sprite;
}

void Car::update()
{
	this->updateTimer();
	this->move();
}

void Car::render(RenderTarget& window)
{
	window.draw(this->sprite);
}