#include "Game.h"

//private functions
void Game::initTextures()
{
	this->textures[0].loadFromFile("Resources/Images/bg.png");
	this->textures[1].loadFromFile("Resources/Images/frog.png");
	this->textures[2].loadFromFile("Resources/Images/carSmall.png");
	this->textures[3].loadFromFile("Resources/Images/carSmallLeft.png");
	this->textures[4].loadFromFile("Resources/Images/carBig.png");
	this->textures[5].loadFromFile("Resources/Images/carBigLeft.png");
	this->textures[6].loadFromFile("Resources/Images/platformShort.png");
	this->textures[7].loadFromFile("Resources/Images/platformLong.png");
	this->textures[8].loadFromFile("Resources/Images/buttonPlay.png");
	this->textures[9].loadFromFile("Resources/Images/buttonQuit.png");
	this->textures[10].loadFromFile("Resources/Images/logo.png");
}

void Game::initVariables()
{
	this->initTextures();
	this->font.loadFromFile("Resources/Fonts/consolas.ttf");

	//game logic
	this->endGame = false;
	this->menu = false;
	this->points = 0;
	this->health = 3;
	this->timerMax = 1200;
	this->timer = this->timerMax;
}

void Game::initWindow()
{
	this->window = nullptr;

	this->videoMode.width = 800;
	this->videoMode.height = 600;

	this->window = new RenderWindow(this->videoMode, "Pogger", Style::Titlebar | Style::Close);
	
	
	this->window->setFramerateLimit(60);
}

void Game::initBackground()
{
	this->background = RectangleShape(Vector2f(800, 600));
	this->background.setFillColor(Color::Blue);
	this->leftBound = RectangleShape(Vector2f(176, 600));
	this->leftBound.setFillColor(Color::Blue);
	this->leftBound.setPosition(0, 0);
	this->rightBound = RectangleShape(Vector2f(176, 600));
	this->rightBound.setFillColor(Color::Blue);
	this->rightBound.setPosition(624, 0);
	this->topBound = RectangleShape(Vector2f(800, 92));
	this->topBound.setFillColor(Color::Blue);
	this->topBound.setPosition(0, 0);
	this->topBackground = RectangleShape(Vector2f(800, 32));
	this->topBackground.setFillColor(Color::Black);
	this->topBackground.setPosition(0, 0);
	this->arena = RectangleShape(Vector2f(14 * 32, 13 * 32));
	this->arena.setTexture(&this->textures[0]);
	this->arena.setPosition(Vector2f(((this->videoMode.width - arena.getSize().x) / 2), (this->videoMode.height - arena.getSize().y) / 2));

	this->timerBarBorder = RectangleShape(Vector2f(164, 20));
	this->timerBarBorder.setFillColor(Color::Red);
	this->timerBarBorder.setPosition(160, 6);
	this->timerBar = RectangleShape(Vector2f(160, 16));
	this->timerBar.setFillColor(Color::Yellow);
	this->timerBar.setPosition(162, 8);

	this->menuBackground.setSize(Vector2f(800, 600));
	this->menuBackground.setPosition(0, 0);
	this->menuBackground.setFillColor(Color::Black);
	this->buttonPlay.setTexture(this->textures[8]);
	this->buttonQuit.setTexture(this->textures[9]);
	this->buttonPlay.setPosition(304, 400);
	this->buttonQuit.setPosition(304, 500);
	this->logo.setTexture(this->textures[10]);
	this->logo.setPosition(227, 25);
}

void Game::initSounds()
{
	this->music.openFromFile("Resources/Sounds/bgm.ogg");
	this->music.setLoop(true);
	this->music.setVolume(100);

	this->musicMenu.openFromFile("Resources/Sounds/menu.ogg");
	this->musicMenu.setLoop(false);
	this->musicMenu.setVolume(100);

	this->musicLoss.openFromFile("Resources/Sounds/loss.ogg");
	this->musicLoss.setLoop(false);
	this->musicLoss.setVolume(100);

	this->musicWin.openFromFile("Resources/Sounds/win.ogg");
	this->musicWin.setLoop(false);
	this->musicWin.setVolume(100);

	this->musicMenu.stop();
	this->music.play();
}

void Game::initText()
{
	this->textHealth.setPosition(16, 8);
	this->textHealth.setCharacterSize(16);
	this->textHealth.setFont(this->font);

	this->textScore.setPosition(400, 8);
	this->textScore.setCharacterSize(16);
	this->textScore.setFont(this->font);
}

void Game::initEntites()
{
	frogs.clear();
	frogs.emplace_back(arena.getPosition().x + arena.getSize().x / 2, arena.getPosition().y + arena.getSize().y - 32, textures[1]);
	this->player = &frogs[frogs.size() - 1];

	lands.clear();
	lands.emplace_back(arena.getPosition().x + 1 * 48, arena.getPosition().y);
	lands.emplace_back(arena.getPosition().x + 3 * 48, arena.getPosition().y);
	lands.emplace_back(arena.getPosition().x + 5 * 48, arena.getPosition().y);
	lands.emplace_back(arena.getPosition().x + 7 * 48, arena.getPosition().y);
	lands.emplace_back(arena.getPosition().x + 9 * 48, arena.getPosition().y);

	cars.clear();
	cars.emplace_back(1, 180, this->arena, textures[3]);
	cars.emplace_back(1, 150, this->arena, textures[3]);
	cars.emplace_back(2, 480, this->arena, textures[4]);
	cars.emplace_back(2, 360, this->arena, textures[4]);
	cars.emplace_back(2, 240, this->arena, textures[4]);
	cars.emplace_back(2, 120, this->arena, textures[4]);
	cars.emplace_back(3, 140, this->arena, textures[5]);
	cars.emplace_back(3, 70, this->arena, textures[5]);
	cars.emplace_back(3, 40, this->arena, textures[5]);
	cars.emplace_back(4, 180, this->arena, textures[3]);
	cars.emplace_back(4, 160, this->arena, textures[3]);
	cars.emplace_back(5, 120, this->arena, textures[2]);
	cars.emplace_back(5, 0, this->arena, textures[2]);
	cars.emplace_back(5, 30, this->arena, textures[2]);

	platforms.clear();
	platforms.emplace_back(1, 300, this->arena, textures[7]);
	platforms.emplace_back(2, 600, this->arena, textures[7]);
	platforms.emplace_back(3, 240, this->arena, textures[6]);
	platforms.emplace_back(4, 600, this->arena, textures[6]);
	platforms.emplace_back(5, 240, this->arena, textures[6]);
	platforms.emplace_back(1, 150, this->arena, textures[7]);
	platforms.emplace_back(2, 300, this->arena, textures[7]);
	platforms.emplace_back(3, 120, this->arena, textures[7]);
	platforms.emplace_back(4, 300, this->arena, textures[6]);
	platforms.emplace_back(5, 120, this->arena, textures[7]);

	this->killzone = RectangleShape(Vector2f(800, 160));
	this->killzone.setPosition(arena.getPosition().x, arena.getPosition().y + 32);
}

void Game::initialization()
{
	this->initVariables();
	this->initBackground();
	this->initSounds();
	this->initText();
	this->initEntites();
}

void Game::checkCollision()
{
	for (auto& e : cars)
	{
		if (e.getSprite()->getGlobalBounds().intersects(this->player->getSprite()->getGlobalBounds()))
		{
			this->killPlayer();
		}
	}
	for (auto& e : lands)
	{
		if (e.getShape()->getGlobalBounds().intersects(this->player->getSprite()->getGlobalBounds()))
		{
			this->killPlayer();
		}
	}
	for (auto& e : frogs)
	{
		if (&e != player)
		{
			if (e.getSprite()->getGlobalBounds().intersects(this->player->getSprite()->getGlobalBounds()))
			{
				this->killPlayer();
			}
		}
	}
	if (killzone.getGlobalBounds().intersects(player->getSprite()->getGlobalBounds()))
	{
		bool safe = false;
		for (auto& e : platforms)
		{
			if (e.getSprite()->getGlobalBounds().intersects(this->player->getSprite()->getGlobalBounds()))
			{
				player->move(e.getSpeed(), this->arena);
				safe = true;
			}
		}
		if (!safe)
		{
			this->killPlayer();
		}
	}
}

void Game::checkFinishline()
{
	if (this->player->getSprite()->getGlobalBounds().top == arena.getPosition().y)
	{
		this->points += this->timer;
		if (frogs.size() == 5)
		{
			this->endGame = true;
			this->music.stop();
			this->musicWin.play();
			this->points += this->timerMax * (this->health - 2);
		}
		else
		{
			frogs.emplace_back(arena.getPosition().x + arena.getSize().x / 2, arena.getPosition().y + arena.getSize().y - 32, textures[1]);
			this->player = &frogs[frogs.size() - 1];
			this->timer = this->timerMax;
			this->timerBar.setScale(this->timer / this->timerMax, 1);
		}
	}
}

void Game::updateTimer()
{
	this->timer--;
	this->timerBar.setScale(this->timer / this->timerMax, 1);
	if (this->timer <= 0)
	{
		this->killPlayer();
	}
}

void Game::killPlayer()
{
	this->health -= 1;
	this->player->respawn();
	this->timer = this->timerMax;
	this->timerBar.setScale(this->timer / this->timerMax, 1);
}

void Game::menuPlay()
{
	this->initialization();
}

void Game::menuQuit()
{
	this->window->close();
}

//constructors, destructors
Game::Game()
{
	this->initWindow();
	this->initialization();
	this->music.stop();
	this->musicMenu.play();
	this->menu = true;
}

Game::~Game()
{
	delete this->window;
}

//accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

//private functions
void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::Escape)
			{
				this->menu = true;
				this->music.stop();
				this->musicLoss.stop();
				this->musicWin.stop();
			}
			else if (this->ev.key.code == Keyboard::Up)
				this->player->move(UP * !this->endGame, this->arena);
			else if (this->ev.key.code == Keyboard::Down)
				this->player->move(DOWN * !this->endGame, this->arena);
			else if (this->ev.key.code == Keyboard::Left)
				this->player->move(LEFT * !this->endGame, this->arena);
			else if (this->ev.key.code == Keyboard::Right)
				this->player->move(RIGHT * !this->endGame, this->arena);
			else if (this->ev.key.code == Keyboard::R)
			{
				this->initialization();
			}
			break;
		case Event::MouseButtonPressed:
			if (this->menu)
			{
				if (this->ev.mouseButton.button == Mouse::Left)
				{
					Vector2f mousePos(this->window->mapPixelToCoords(Mouse::getPosition(*this->window)));
					if (this->buttonPlay.getGlobalBounds().contains(mousePos))
					{
						this->menuPlay();
					}
					if (this->buttonQuit.getGlobalBounds().contains(mousePos))
					{
						this->menuQuit();
					}
				}
			}
			break;
		}
	}
}

void Game::update()
{
	this->pollEvents();

	if (!this->endGame && this->health <= 0)
	{
		this->endGame = true;
		this->points = 0;
		this->music.stop();
		this->musicLoss.play();
	}

	if (!this->endGame and !this->menu)
	{
		this->updateTimer();

		for (auto& e : cars)
		{
			e.update();
		}
		for (auto& e : platforms)
		{
			e.update();
		}

		this->checkCollision();
		this->checkFinishline();

		stringstream ss;
		ss << "Lives left: " << this->health;
		this->textHealth.setString(ss.str());
	}
	stringstream ss;
	ss << "Score: " << this->points;
	this->textScore.setString(ss.str());


}

void Game::render()
{
	//draw background
	this->window->clear(Color::Black);
	this->window->draw(background);
	this->window->draw(arena);

	//draw game objects
	for (auto& e : platforms)
	{
		e.render(*this->window);
	}
	for (auto& e : frogs)
	{
		e.render(*this->window);
	}
	for (auto& e : cars)
	{
		e.render(*this->window);
	}
	
	//draw foreground
	this->window->draw(leftBound);
	this->window->draw(rightBound);
	this->window->draw(topBound);
	this->window->draw(topBackground);

	this->window->draw(textHealth);
	this->window->draw(timerBarBorder);
	this->window->draw(timerBar);
	this->window->draw(textScore);

	//draw menu
	if (this->menu)
	{
		this->window->draw(menuBackground);
		this->window->draw(logo);
		this->window->draw(buttonPlay);
		this->window->draw(buttonQuit);
	}

	this->window->display();
}
