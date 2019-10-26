#include "Board.h"
#include "Ship.h"


#include <iostream>



Board::Board(Player& player) 
    : player(player)
{
	for (int i = 0; i < brd.size(); ++i)
		for (int j = 0; j < brd.size(); ++j)
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

// TODO Lots of code repetition here. Extract some of it to seperate functions and see if you can get rid of some of the repeating code!
void Board::PlaceShips()
{
	for (int i = 0; i < player.Ships.size(); ++i)
	{
		bool locationVerified{ false };

		while (locationVerified == false)
		{
			InputShipCoordinates(player.Ships.at(i));

			locationVerified = isTileOccupied(player.Ships.at(i));
			
			if (locationVerified == true)
			{
				for (int j = 1; j < player.Ships.at(i).GetLength(); ++j)
				{
					if (player.Ships.at(i).orientation == Ship::Orientation::Vertical)
					{
						brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y] = '#';
						brd[player.Ships.at(i).location.x + j][player.Ships.at(i).location.y] = '#';
					}
					else if(player.Ships.at(i).orientation == Ship::Orientation::Horizontal)
					{
						brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y] = '#';
						brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y + j] = '#';
					}
					else if (player.Ships.at(i).orientation == Ship::Orientation::DiagonalLeft)
					{
						brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y] = '#';
						brd[player.Ships.at(i).location.x + j][player.Ships.at(i).location.y + j] = '#';
					}
					else if (player.Ships.at(i).orientation == Ship::Orientation::DiagonalRight)
					{
						brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y] = '#';
						brd[player.Ships.at(i).location.x + j][player.Ships.at(i).location.y - j] = '#';
					}
				}
					
				std::cout << "Press enter to preview your ship's location";
				std::cin.get();
				std::cout << std::endl;

				system("cls");
				Draw();

				char input{};
				std::cout << "Place your ship here?(Y/N)";
				std::cin >> input;

				if (input == 'N' ||input == 'n')
				{
					for (int j = 1; j < player.Ships.at(i).GetLength(); ++j)
					{
						switch (player.Ships.at(i).orientation)
						{
						case Ship::Orientation::Horizontal:
							brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y] = '.';
							brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y + j] = '.';
							break;
						case Ship::Orientation::Vertical:
							brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y] = '.';
							brd[player.Ships.at(i).location.x + j][player.Ships.at(i).location.y] = '.';
							break;
						case Ship::Orientation::DiagonalLeft:
							brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y] = '.';
							brd[player.Ships.at(i).location.x + j][player.Ships.at(i).location.y + j] = '.';
							break;
						case Ship::Orientation::DiagonalRight:
							brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y] = '.';
							brd[player.Ships.at(i).location.x + j][player.Ships.at(i).location.y - j] = '.';
						}
					}
					locationVerified = false;
				}
				else if (input == 'Y' || input == 'y')
				{
					locationVerified = true;
				}
			}
		}
	}
}

void Board::InputShipCoordinates(Ship& ship)
{
	std::unordered_map<char, int> coords{ {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9} };
	int x{};
	char y{};
	bool isValidLocation{ false };

	while (isValidLocation == false)
	{
		system("cls");
		Draw();

		std::cout << "Enter the coordinates of your " << ship.GetType() << "(Size: " << ship.GetLength() << ")" << ". Example(\"H5\")" << std::endl;
		std::cin >> y >> x;

		if (x >= 1 && x <= brd.size() && y >= 'A' && y <= 'J')
		{
			isValidLocation = true;
			ship.location.x = x - 1;
			ship.location.y = coords[y];
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
			if (ship.location.x + ship.GetLength() > brd.size() || ship.location.y - ship.GetLength() < -1)
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

bool Board::isTileOccupied(Ship& ship)
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
}
