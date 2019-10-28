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

	while (runGame)
	{
		CLEARSCRN;

		brdP1.ClearBoard();
		brdP2.ClearBoard();
		player1Hits.ClearBoard();
		player2Hits.ClearBoard();

		StartGame();

		player1.isMyTurn = true;
		player2.isMyTurn = false;

		// TODO see if you can get rid of the player1Hits and player2Hits boards and use the main boards instead
		// Also consider not showing the current player's board when it is his turn. This way the other player wouldnt need
		// to constantly be looking away from the screen.
		while (true)
		{
			CLEARSCRN;

			if (player1.isMyTurn)
			{
				
				if (!ProcessPlayerTurn(player1, brdP1, player1Hits, player2, brdP2))
					break;
			}
			else if (player2.isMyTurn)
			{
				if (!ProcessPlayerTurn(player2, brdP2, player2Hits, player1, brdP1))
					break;
			}
		}

		if (brdP1.isAllShipsDestroyed())
		{
			std::cout << player2.GetName() << " has won the game! Congrats!" << std::endl;
			++player2.score;

		}
		else
		{
			std::cout << player1.GetName() << " has won the game! Congrats!" << std::endl;
			++player1.score;
		}

		char input{};
		do
		{
			std::cout << "\n\nPlay again?(Y/N): ";
			std::cin >> input;
		} while (input != 'Y' && input != 'y' && input != 'N' && input != 'n');

		if (input == 'Y' || input == 'y')
			runGame = true;
		else if (input == 'N' || input == 'n')
			break;
	}
}

bool Game::ProcessPlayerTurn(Player& playerInTurn, Board& brdPlayerInTurn, Board& playerInTurnHits, Player& otherPlayer, Board& brdOtherPlayer)
{
	std::cout << "It is " << playerInTurn.GetName() << "'s turn to shoot! " << otherPlayer.GetName() << " please look away from the screen.\n";
	std::cout << "Press enter to continue\n";
	std::cin.ignore();
	std::cin.get();

	while (playerInTurn.isMyTurn)
	{
		CLEARSCRN;

		std::cout << "Your score: " << playerInTurn.score << "\tEnemy score: " << otherPlayer.score << std::endl;
		std::cout << "\n\n\n============ ENEMY BOARD ============\n\n";
		playerInTurnHits.Draw();
		std::cout << "X = Miss\tO = Hit\n";

		std::cout << "\n\n\n============ YOUR BOARD ============\n\n";
		brdPlayerInTurn.Draw();
		std::cout << "X = Miss\tO = Hit\n";

		int x{};
		char y{};
		Location hitLocation{};
		std::cout << "Give your artillery crew the coordinates to fire at!(example: \"H4\")\n";
		std::cin >> y >> x;

		hitLocation = { x - 1, Board::coords.at(y) };

		if (brdOtherPlayer.GetSymbolFromBoard(hitLocation) == '#')
		{
			playerInTurnHits.DrawSymbolOnBoard(hitLocation, 'O');
			brdOtherPlayer.DrawSymbolOnBoard(hitLocation, 'O');
			playerInTurn.isMyTurn = true;

			CLEARSCRN;
			std::cout << "\n\n\n============ ENEMY BOARD ============\n\n";
			playerInTurnHits.Draw();
			std::cout << "X = Miss\tO = Hit\n";

			std::cout << "\n\n\n============ YOUR BOARD ============\n\n";
			brdPlayerInTurn.Draw();

			if (brdOtherPlayer.isAllShipsDestroyed())
			{
				return false;
			}

			std::cout << "You hit an enemy ship! You may fire again! 1. Understood 2. Huh?";
		}
		else if (brdOtherPlayer.GetSymbolFromBoard(hitLocation) == 'O')
		{
			CLEARSCRN;
			std::cout << "\n\n\n============ ENEMY BOARD ============\n\n";
			playerInTurnHits.Draw();
			std::cout << "X = Miss\tO = Hit\n";

			std::cout << "\n\n\n============ YOUR BOARD ============\n\n";
			brdPlayerInTurn.Draw();

			std::cout << "Error! You have already fired at those coordinates. Please try again. 1. Understood 2. Huh?";
		}
		else
		{
			playerInTurnHits.DrawSymbolOnBoard(hitLocation, 'X');
			brdOtherPlayer.DrawSymbolOnBoard(hitLocation, 'X');
			playerInTurn.isMyTurn = false;
			otherPlayer.isMyTurn = true;

			CLEARSCRN;
			std::cout << "\n\n\n============ ENEMY BOARD ============\n\n";
			playerInTurnHits.Draw();
			std::cout << "X = Miss\tO = Hit\n";

			std::cout << "\n\n\n============ YOUR BOARD ============\n\n";
			brdPlayerInTurn.Draw();

			std::cout << "You miss! 1. Understood 2. Huh?";
		}

		char input{};
		do
		{
			std::cin >> input;
		} while (input != '1' && input != '2');
	}

	return true;
}
