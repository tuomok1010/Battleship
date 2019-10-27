#include "Game.h"
#include "config.h"

#include <iostream>
#include <string>

Game::Game() 
    : brdP1(player1), brdP2(player2), player1Hits(player2), player2Hits(player1)
{
}

void Game::InputPlayerInfo()
{
	std::string name{};

	std::cout << "========== BATTLESHIP GAME ==========\n\n" << "Enter player 1 name: ";
	std::getline(std::cin, name);
	player1.SetName(name);

	std::cout << "Enter player 2 name: ";
	std::getline(std::cin, name);
	player2.SetName(name);

	CLEARSCRN;
	
}

void Game::StartGame()
{
	InputPlayerInfo();

	std::cout << player1.GetName() << ", it is your turn to place your ships! " << player2.GetName() << " please look away from the screen!\n";
	std::cout << "Press enter to continue" << std::flush;
	std::cin.get();
	brdP1.PlaceShips();

	CLEARSCRN;

	std::cout << player2.GetName() << ", it is your turn to place your ships! " << player1.GetName() << " please look away from the screen!\n";
	std::cout << "Press enter to continue" << std::flush;
	std::cin.ignore();
	std::cin.get();
	brdP2.PlaceShips();

	CLEARSCRN;
}

void Game::RunGame()
{
	player1.isMyTurn = true;
	player2.isMyTurn = false;

	while (!brdP1.isAllShipsDestroyed() && !brdP2.isAllShipsDestroyed())
	{
		CLEARSCRN;

		if (player1.isMyTurn)
		{
			std::cout << "It is " << player1.GetName() << "'s turn to shoot! " << player2.GetName() << " please look away from the screen.\n";
			std::cout << "Press enter to continue\n";
			std::cin.ignore();
			std::cin.get();
			
			while (player1.isMyTurn)
			{
				CLEARSCRN;

				std::cout << "\n\n\n============ ENEMY BOARD ============\n\n";
				player1Hits.Draw();
				std::cout << "X = Miss\tO = Hit\n";

				std::cout << "\n\n\n============ YOUR BOARD ============\n\n";
				brdP1.Draw();

				int x{};
				char y{};
				Location hitLocation{};
				std::cout << "Give your artillery crew the coordinates to fire at!(example: \"H 4\")\n";
				std::cin >> y >> x;

				//hitLocation = { x - 1, Board::coords.at(y) };
				hitLocation.x = x - 1;
				hitLocation.y = Board::coords.at(y);

				if (brdP2.GetSymbolFromBoard(hitLocation) == '#')
				{
					player1Hits.DrawSymbolOnBoard(hitLocation, 'O');
					brdP2.DrawSymbolOnBoard(hitLocation, 'O');
					player1.isMyTurn = true;

					std::cout << "You hit an enemy ship! You may fire again! 1. Understood 2. Huh?";
				}
				else if (brdP2.GetSymbolFromBoard(hitLocation) == 'O')
				{
					std::cout << "Error! You have already fired at those coordinates. Please try again. 1. Understood 2. Huh?";
				}
				else
				{			
					player1Hits.DrawSymbolOnBoard(hitLocation, 'X');
					brdP2.DrawSymbolOnBoard(hitLocation, 'X');
					player1.isMyTurn = false;
					player2.isMyTurn = true;

					std::cout << "You miss! 1. Understood 2. Huh?";
				}

				char input{};
				do
				{
					std::cin >> input;
				} while (input != '1' && input != '2');

				CLEARSCRN;
				std::cout << "\n\n\n============ ENEMY BOARD ============\n\n";
				player1Hits.Draw();
				std::cout << "X = Miss\tO = Hit\n";

				std::cout << "\n\n\n============ YOUR BOARD ============\n\n";
				brdP1.Draw();
			}
		}
		else if (player2.isMyTurn)
		{
			std::cout << "It is " << player2.GetName() << "'s turn to shoot! " << player1.GetName() << " please look away from the screen.\n";
			std::cout << "Press enter to continue" << std::flush;
			std::cin.ignore();
			std::cin.get();

			while (player2.isMyTurn)
			{

			}
		}
	}
}
