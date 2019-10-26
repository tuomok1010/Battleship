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

	std::unordered_map<char, int> coords{ {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9} };
	for (int i = 0; i < player.Ships.size(); ++i)
	{
		int x{};
		char y{};
		bool locationVerified{ false };

		while (locationVerified == false)
		{
			system("cls");
			Draw();

			std::cout << "Enter the coordinates of your " << player.Ships.at(i).GetType() << "(Size: " << player.Ships.at(i).GetLength() << ")" << ". Example(\"H5\")" << std::endl;
			std::cin >> y >> x;

			player.Ships.at(i).location.x = x - 1;
			player.Ships.at(i).location.y = coords[y];

			char selection{};
			std::cout << "Would you like to place your ship \n1. Horizontally \n2. Vertically \n3. Diagonal(top left to bottom right) \n4. Diagonal(top right to bottom left)\n";
			std::cin >> selection;

			switch (selection)
			{
			case '1':
				player.Ships.at(i).orientation = Ship::Orientation::Horizontal;
				break;
			case '2':
				player.Ships.at(i).orientation = Ship::Orientation::Vertical;
				break;
			case '3':
				player.Ships.at(i).orientation = Ship::Orientation::DiagonalLeft;
				break;
			case '4':
				player.Ships.at(i).orientation = Ship::Orientation::DiagonalRight;
				break;
			default:
				std::cout << "Invalid input!" << std::endl;
			}

			std::cin.ignore();

			for (int j = 1; j < player.Ships.at(i).GetLength(); ++j)
			{
				// Check if any of the cells in the board are occupied
				// TODO consider extracting all this logic to a separate function
				if (player.Ships.at(i).orientation == Ship::Orientation::Horizontal)
				{
					if (brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y] == '#' || brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y + j] == '#')
					{
						std::cout << "Error! The coordinates are already occupied! Pick another location or try rotating the ship!" << std::endl;
						std::cin.get();
						//brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y] = '.';
						brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y + j] = '.';
						locationVerified = false;
						break;
					}
					else
						locationVerified = true;
				}
				else if (player.Ships.at(i).orientation == Ship::Orientation::Vertical)
				{
					if (brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y] == '#' || brd[player.Ships.at(i).location.x + j][player.Ships.at(i).location.y] == '#')
					{
						std::cout << "Error! The coordinates are already occupied! Pick another location or try rotating the ship!" << std::endl;
						std::cin.get();
						//brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y] = '.';
						brd[player.Ships.at(i).location.x + j][player.Ships.at(i).location.y] = '.';
						locationVerified = false;
						break;
					}
					else
						locationVerified = true;
				}
				else if (player.Ships.at(i).orientation == Ship::Orientation::DiagonalLeft)
				{
					if (brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y] == '#' || brd[player.Ships.at(i).location.x + j][player.Ships.at(i).location.y] == '#')
					{
						std::cout << "Error! The coordinates are already occupied! Pick another location or try rotating the ship!" << std::endl;
						std::cin.get();
						//brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y] = '.';
						brd[player.Ships.at(i).location.x + j][player.Ships.at(i).location.y + j] = '.';
						locationVerified = false;
						break;
					}
					else
						locationVerified = true;
				}
				else if (player.Ships.at(i).orientation == Ship::Orientation::DiagonalRight)
				{
					if (brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y] == '#' || brd[player.Ships.at(i).location.x + j][player.Ships.at(i).location.y] == '#')
					{
						std::cout << "Error! The coordinates are already occupied! Pick another location or try rotating the ship!" << std::endl;
						std::cin.get();
						//brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y] = '.';
						brd[player.Ships.at(i).location.x + j][player.Ships.at(i).location.y - j] = '.';
						locationVerified = false;
						break;
					}
					else
						locationVerified = true;
				}
			}

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

				if (input == 'N')
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
				else if (input == 'Y')
				{
					locationVerified = true;
				}
			}

		}
	}
}
