#include "Board.h"
#include "config.h"
#include "Ship.h"


#include <iostream>

const std::unordered_map<char, int> Board::coords = { {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9} };

Board::Board(Player& player) 
    : player(player)
{
	for (size_t i = 0; i < brd.size(); ++i)
		for (size_t j = 0; j < brd.size(); ++j)
			brd[i][j] = '.';
}

void Board::Draw()
{
    std::cout << "\tA B C D E F G H I J\n";

    for(int i = 0; i < size; ++i)
    {
        std::cout << i + 1 << " \t";

        for(int j = 0; j < size; ++j)
        {
            std::cout << brd[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Board::PlaceShips()
{
	for (size_t i = 0; i < player.Ships.size(); ++i)
	{
		bool locationVerified{ false };

		while (locationVerified == false)
		{
			InputShipCoordinates(player.Ships.at(i));

			locationVerified = AreTilesOccupied(player.Ships.at(i));
			
			if (locationVerified == true)
			{
				PlaceShip(player.Ships.at(i));
					
				std::cout << "Press enter to preview your ship's location";
				std::cin.get();
				std::cout << std::endl;

				CLEARSCRN;
				Draw();

				locationVerified = VerifyShipPlacement(player.Ships.at(i));
			}
		}
	}
}

void Board::InputShipCoordinates(Ship& ship)
{
	unsigned int x{};
	char y{};
	bool isValidLocation{ false };

	while (isValidLocation == false)
	{
		CLEARSCRN;
		Draw();

		std::cout << "Enter the coordinates of your " << ship.GetType() << "(Size: " << ship.GetLength() << ")" << ". Example(\"H5\")" << std::endl;
		std::cin >> y >> x;

		if (x >= 1 && x <= brd.size() && y >= 'A' && y <= 'J')
		{
			isValidLocation = true;
			ship.location.x = x - 1;
			ship.location.y = coords.at(y);
		}
		else
		{
			std::cout << "Invalid Coordinates! Try again." << std::endl;
			isValidLocation = false;
		}

		isValidLocation = false;

		char selection{};
		std::cout << "Would you like to place your ship \n1. Horizontally \n2. Vertically \n3. Diagonal(top left to bottom right) \n4. Diagonal(top right to bottom left)\n";
		std::cin >> selection;

		switch (selection)
		{
		case '1':
			if (ship.location.y + ship.GetLength() > brd.size())
			{
				std::cout << "Error! Ship would go out of board bounds!\n";
				std::cout << "Press enter to try again." << std::endl;
				isValidLocation = false;
				std::cin.ignore();
				std::cin.get();
				break;
			}
			ship.orientation = Ship::Orientation::Horizontal;
			isValidLocation = true;
			break;
		case '2':
			if (ship.location.x + ship.GetLength() > brd.size())
			{
				std::cout << "Error! Ship would go out of board bounds!\n";
				std::cout << "Press enter to try again." << std::endl;
				isValidLocation = false;
				std::cin.ignore();
				std::cin.get();
				break;
			}
			ship.orientation = Ship::Orientation::Vertical;
			isValidLocation = true;
			break;
		case '3':
			if (ship.location.x + ship.GetLength() > brd.size() || ship.location.y + ship.GetLength() > brd.size())
			{
				std::cout << "Error! Ship would go out of board bounds!\n";
				std::cout << "Press enter to try again." << std::endl;
				isValidLocation = false;
				std::cin.ignore();
				std::cin.get();
				break;
			}
			ship.orientation = Ship::Orientation::DiagonalLeft;
			isValidLocation = true;
			break;
		case '4':
			if (ship.location.x + ship.GetLength() > brd.size() || ship.location.y - ship.GetLength() < 0)
			{
				std::cout << "Error! Ship would go out of board bounds!\n";
				std::cout << "Press enter to try again." << std::endl;
				isValidLocation = false;
				std::cin.ignore();
				std::cin.get();
				break;
			}
			ship.orientation = Ship::Orientation::DiagonalRight;
			isValidLocation = true;
			break;
		default:
			std::cout << "Invalid input!" << std::endl;
			std::cin.ignore();
			std::cin.get();
			isValidLocation = false;
		}
	}
}

bool Board::AreTilesOccupied(const Ship& ship)
{
	for (int j = 1; j < ship.GetLength(); ++j)
	{
		// Check if any of the cells in the board are occupied
		// TODO consider extracting all this logic to a separate function
		if (ship.orientation == Ship::Orientation::Horizontal)
		{
			if (brd[ship.location.x][ship.location.y] == '#' || brd[ship.location.x][ship.location.y + j] == '#')
			{
				std::cout << "Error! The coordinates are already occupied! Pick another location or try rotating the ship!" << std::endl;
				std::cin.ignore();
				std::cin.get();
				brd[ship.location.x][ship.location.y + j] = '.';
				return false;
			}
			else
			{
				return true;
			}		
		}
		else if (ship.orientation == Ship::Orientation::Vertical)
		{
			if (brd[ship.location.x][ship.location.y] == '#' || brd[ship.location.x + j][ship.location.y] == '#')
			{
				std::cout << "Error! The coordinates are already occupied! Pick another location or try rotating the ship!" << std::endl;
				std::cin.ignore();
				std::cin.get();
				brd[ship.location.x + j][ship.location.y] = '.';
				return false;
			}
			else
			{
				return true;
			}
		}
		else if (ship.orientation == Ship::Orientation::DiagonalLeft)
		{
			if (brd[ship.location.x][ship.location.y] == '#' || brd[ship.location.x + j][ship.location.y] == '#')
			{
				std::cout << "Error! The coordinates are already occupied! Pick another location or try rotating the ship!" << std::endl;
				std::cin.ignore();
				std::cin.get();
				brd[ship.location.x + j][ship.location.y + j] = '.';
				return false;
			}
			else
			{
				return true;
			}
		}
		else if (ship.orientation == Ship::Orientation::DiagonalRight)
		{
			if (brd[ship.location.x][ship.location.y] == '#' || brd[ship.location.x + j][ship.location.y] == '#')
			{
				std::cout << "Error! The coordinates are already occupied! Pick another location or try rotating the ship!" << std::endl;
				std::cin.ignore();
				std::cin.get();
				brd[ship.location.x + j][ship.location.y - j] = '.';
				return false;
			}
			else
			{
				return true;
			}
		}
	}

	return false;
}

void Board::PlaceShip(const Ship& ship)
{
	for (int j = 1; j < ship.GetLength(); ++j)
	{
		if (ship.orientation == Ship::Orientation::Vertical)
		{
			brd[ship.location.x][ship.location.y] = '#';
			brd[ship.location.x + j][ship.location.y] = '#';
		}
		else if (ship.orientation == Ship::Orientation::Horizontal)
		{
			brd[ship.location.x][ship.location.y] = '#';
			brd[ship.location.x][ship.location.y + j] = '#';
		}
		else if (ship.orientation == Ship::Orientation::DiagonalLeft)
		{
			brd[ship.location.x][ship.location.y] = '#';
			brd[ship.location.x + j][ship.location.y + j] = '#';
		}
		else if (ship.orientation == Ship::Orientation::DiagonalRight)
		{
			brd[ship.location.x][ship.location.y] = '#';
			brd[ship.location.x + j][ship.location.y - j] = '#';
		}
	}
}

bool Board::VerifyShipPlacement(const Ship& ship)
{
	char input{};
	std::cout << "Place your ship here?(Y/N)";
	std::cin >> input;

	do
	{
		if (input == 'N' || input == 'n')
		{
			for (int j = 1; j < ship.GetLength(); ++j)
			{
				switch (ship.orientation)
				{
				case Ship::Orientation::Horizontal:
					brd[ship.location.x][ship.location.y] = '.';
					brd[ship.location.x][ship.location.y + j] = '.';
					break;
				case Ship::Orientation::Vertical:
					brd[ship.location.x][ship.location.y] = '.';
					brd[ship.location.x + j][ship.location.y] = '.';
					break;
				case Ship::Orientation::DiagonalLeft:
					brd[ship.location.x][ship.location.y] = '.';
					brd[ship.location.x + j][ship.location.y + j] = '.';
					break;
				case Ship::Orientation::DiagonalRight:
					brd[ship.location.x][ship.location.y] = '.';
					brd[ship.location.x + j][ship.location.y - j] = '.';
				}
			}
			return false;
		}
		else if (input == 'Y' || input == 'y')
		{
			return true;
		}
		else
		{
			std::cout << "Invalid input. Try again" << std::endl;
		}

	} while (input != 'Y' && input != 'y' && input != 'N' && input != 'n');

	return true;
}

bool Board::isShipHit(const Location& HitLocation)
{
	if (brd[HitLocation.x][HitLocation.y] == '#')
	{
		return true;
	}

	return false;
}

bool Board::isAllShipsDestroyed()
{
	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = 0; j < size; ++j)
		{
			if (brd[i][j] == '#')
				return false;
		}
	}
	return true;
}

void Board::DrawSymbolOnBoard(const Location& location, char symbol)
{
	brd[location.x][location.y] = symbol;
}

char Board::GetSymbolFromBoard(const Location& location)
{
	return brd[location.x][location.y];
}

void Board::ClearBoard()
{
	for (size_t i = 0; i < size; ++i)
		for (size_t j = 0; j < size; ++j)
			brd[i][j] = '.';
}
