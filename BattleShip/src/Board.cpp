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

void Board::PlaceShips()
{
	Draw();

	std::unordered_map<char, int> coords{ {'A', 1}, {'B', 2}, {'C', 3}, {'D', 4}, {'E', 5}, {'F', 6}, {'G', 7}, {'H', 8}, {'I', 9}, {'J', 10} };
	for (int i = 0; i < player.Ships.size(); ++i)
	{
		int x{};
		char y{};

		std::cout << "Enter the coordinates of your " << player.Ships.at(i).GetType() << std::endl;
		std::cin >> x >> y;

		player.Ships.at(i).location.x = x;
		player.Ships.at(i).location.y = coords[y];

		for (int j = 0; j < player.Ships.at(i).GetLength(); ++j)
		{
			brd[player.Ships.at(i).location.x][player.Ships.at(i).location.y] = '#';
			brd[player.Ships.at(i).location.x + j][player.Ships.at(i).location.y] = '#';
		}
	}

}
