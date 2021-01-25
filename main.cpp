#include "Game.h"

int main()
{
	//init srand
	srand(static_cast<unsigned>(time(NULL)));

	//init game engine
	Game game;

	//game loop
	while (game.running())
	{
		//update
		game.update();

		//render
		game.render();
	}

	return 0;
}