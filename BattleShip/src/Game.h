#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Board.h"

class Game 
{
public:
	Game();
	void StartGame();
	void RunGame();

    Player player1;
    Player player2;
private:
    Board brdP1;
    Board brdP2;
};

#endif