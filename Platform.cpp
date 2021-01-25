#include "Platform.h"

void Platform::initSprite(Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Platform::initVariables(int type, float timerStart, RectangleShape& arena)
{
	this->ylevel = type;
	switch (type)
	{
	case 1:
		this->timerMax = 300;
		this->speed = 2.f;
		this->reverse = false;
		break;
	case 2:
		this->timerMax = 600;
		this->speed = -1.f;
		this->reverse = true;
		break;
	case 3:
		this->timerMax = 240;
		this->speed = 3.f;
		this->reverse = false;
		break;
	case 4:
		this->timerMax = 600;
		this->speed = 1.f;
		this->reverse = false;
		break;
	case 5:
		this->timerMax = 240;
		this->speed = -3.f;
		this->reverse = true;
		break;
	}
	this->timer = timerStart;
}

void Platform::updateTimer()
{
	this->timer += 1;
	if (this->timer >= this->timerMax)
	{
		this->timer = 0;
		this->respawn();
	}
}

void Platform::move()
{
	this->sprite.move(speed, 0);
}

void Platform::respawn()
{
	if (!this->reverse)
	{
		this->sprite.setPosition(this->arena.getGlobalBounds().left - this->sprite.getGlobalBounds().width, this->arena.getGlobalBounds().top + 224 - 32 * (1 + this->ylevel));
	}
	else
	{
		this->sprite.setPosition(this->arena.getGlobalBounds().left + this->arena.getGlobalBounds().width, this->arena.getGlobalBounds().top + 224 - 32 * (1 + this->ylevel));
	}
}

Platform::Platform(int type, float timerStart, RectangleShape& arena, Texture& texture) :arena(arena)
{
	this->initVariables(type, timerStart, arena);
	this->initSprite(texture);
}

Platform::~Platform()
{
}

Sprite* Platform::getSprite()
{
	return &this->sprite;
}

float Platform::getSpeed()
{
	return this->speed;
}

void Platform::update()
{
	this->updateTimer();
	this->move();
}

void Platform::render(RenderTarget& window)
{
	window.draw(this->sprite);
}