#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include "Frog.h"
#include "Car.h"
#include "Platform.h"
#include "Land.h"

using namespace std;
using namespace sf;

/*
Class acting as the game engine.
*/

class Game
{
private:
	//Variables
	//Window
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;

	RectangleShape background;
	RectangleShape leftBound;
	RectangleShape rightBound;
	RectangleShape topBound;
	RectangleShape topBackground;
	RectangleShape arena;

	RectangleShape timerBarBorder;
	RectangleShape timerBar;

	//Menu
	bool menu;
	RectangleShape menuBackground;
	Sprite buttonPlay;
	Sprite buttonHelp;
	Sprite buttonSettings;
	Sprite buttonQuit;

	//Mouse positions
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	//Game logic
	bool endGame;
	int health;
	int points;
	float timerMax;
	float timer;

	Frog* player;
	vector<Frog> frogs;
	vector<Car> cars;
	vector<Land> lands;
	vector<Platform> platforms;
	RectangleShape killzone;

	//Resources
	Music music;
	Music musicLoss;
	Music musicWin;
	Texture arenaTexture;
	Texture textures[12];
	Font font;
	Text textHealth;
	Text textScore;

	//Private functions
	void initTextures();
	void initVariables();
	void initWindow();
	void initBackground();
	void initSounds();
	void initEntites();

	void initialization();

	void checkCollision();
	void checkFinishline();
	void updateTimer();
	void killPlayer();

	void menuPlay();
	void menuHelp();
	void menuSettings();
	void menuQuit();
public:
	//Constructors & Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	bool shut;

	//Functions

	void pollEvents();

	void update();

	void render();
};