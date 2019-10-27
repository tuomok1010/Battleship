#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Board.h"

class Game 
{
public:
	Game();
	void InputPlayerInfo();
	void StartGame();
	void RunGame();

    Player player1;
    Player player2;
private:
    Board brdP1;
    Board brdP2;

	Board player1Hits;
	Board player2Hits;
};

#endif