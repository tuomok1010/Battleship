#ifndef SHIP_H
#define SHIP_H

#include "Location.h"

#include <string>

class Ship
{
public:
    Ship(unsigned int length, std::string type) :
        length(length), type(type)
	{
	}

	bool isDestroyed{ false };

	inline int GetLength() const { return length; }
	inline std::string GetType() const { return type; }

    Location location{};
    unsigned int length{};
	std::string type{};

public:
	enum class Orientation
	{
		Horizontal, Vertical, DiagonalLeft, DiagonalRight
	};

	Orientation orientation = Orientation::Horizontal;
};

#endif