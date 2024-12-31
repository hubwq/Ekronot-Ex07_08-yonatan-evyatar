#include <iostream>
#include "Manager.h"

#include "BoardSizeExeption.h"

void main()
{
	Manager board("rnbkqbnrpppp#ppp################################PPP#PPPPRNBKQBNR0");

	std::string move = "";
	while (1)
	{
		board.printBoard();

		std::cout << "Player " << ((board.GetTurn()) ? "Black\n" : "White\n") << "Enter your move:" << std::endl;
		std::cin >> move;

		try
		{
			board.MoveBoard(move);
		}
		catch(MoveExeption e)
		{
			printf(e.what());
			std::cout << std::endl;
		}
		catch (BoardSizeExeption e)
		{
			printf(e.what());
			std::cout << std::endl;
		}
	}
}