#ifndef BOARD_H
#define BOARD_H

#include "Player.h"

#include <string>
#include <unordered_map>
#include <array>

class Board
{
public:
    Board(Player& player);

    void Draw();
    void PlaceShips();
    void ProcessHits();

private:
    static constexpr int size{10};
	std::array<std::array<char, 10>, 10> brd{};
	char shipSymbol{ '#' };
    Player& player;
};

#endif