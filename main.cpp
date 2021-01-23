#include "Game.h"

int main()
{
	//Init srand
	srand(static_cast<unsigned>(time(NULL)));

	//Init game engine
	Game game;

	//Game loop
	while (game.running() && !game.shut)
	{
		//Update
		game.update();

		//Render
		game.render();
	}

	//End
	return 0;
}