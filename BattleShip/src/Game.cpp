#include "Game.h"

Game::Game() 
    : brdP1(player1), brdP2(player2)
{
}

void Game::StartGame()
{
	brdP1.PlaceShips();
}
