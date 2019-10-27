#ifndef PLAYER_H
#define PLAYER_H

#include "Ship.h"

#include <string>
#include <vector>
#include <unordered_map>

class Player
{
public:
	Player()
	{
		Ships.emplace_back(shipTypes.at("Carrier"));
		Ships.emplace_back(shipTypes.at("Battleship"));
		Ships.emplace_back(shipTypes.at("Destroyer"));
		Ships.emplace_back(shipTypes.at("Submarine"));
		Ships.emplace_back(shipTypes.at("Patrol Boat"));
	}

	inline std::string GetName() const { return name; }
	inline void SetName(std::string name) { this->name = name; }

	std::vector<Ship> Ships;
	bool isMyTurn{ false };

private:
    std::string name{};
    int score{};
	const std::unordered_map<std::string, Ship> shipTypes
	{
		{"Carrier", Ship(5, "Carrier")},
		{"Battleship", Ship(4, "BattleShip")},
		{"Destroyer", Ship(3, "Destroyer")},
		{"Submarine", Ship(3, "Submarine")},
		{"Patrol Boat", Ship(2, "Patrol Boat")}
	};

};

#endif