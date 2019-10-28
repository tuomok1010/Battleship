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
	void InputShipCoordinates(Ship& ship);
	bool AreTilesOccupied(const Ship& ship);
	void PlaceShip(const Ship& ship);
	bool VerifyShipPlacement(const Ship& ship);
    bool isShipHit(const Location& HitLocation);
	bool isAllShipsDestroyed();
	void DrawSymbolOnBoard(const Location& location, char symbol);
	char GetSymbolFromBoard(const Location& location);
	void ClearBoard();

	const static std::unordered_map<char, int> coords;
private:
    static constexpr unsigned int size{10};
	std::array<std::array<char, size>, size> brd{};
	char shipSymbol{ '#' };
    Player& player;
};

#endif