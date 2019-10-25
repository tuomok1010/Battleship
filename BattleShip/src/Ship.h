#ifndef SHIP_H
#define SHIP_H

#include "Location.h"

#include <string>

class Ship
{
public:
    Ship(int length, std::string type) :
        length(length), type(type)
	{
	}

	bool isDestroyed{ false };
	bool isVertical{ false };

	inline int GetLength() const { return length; }
	inline std::string GetType() const { return type; }

    Location location{};

private:
    int length{};
	std::string type{};
};

#endif