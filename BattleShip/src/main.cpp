#include <iostream>

#include "Game.h"

int main()
{
	Game game;

	game.StartGame();
	game.RunGame();

	std::cin.get();
    return 0;
}
