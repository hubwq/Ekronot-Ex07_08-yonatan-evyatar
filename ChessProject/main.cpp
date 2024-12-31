#include "../Frontend/Pipe.h"
#include <iostream>
#include <thread>
#include "Piece.h"
#include "Manager.h"

using std::cout;
using std::endl;
using std::string;

#define WHITE 0
#define BLACK 1
#define MAX_BOARD_ROWS 8
#define MAX_BOARD_COLS 8
#define MIN_BOARD_ROWS 0
#define MIN_BOARD_COLS 0




// connect to pipe
Pipe connect()
{
	srand(time_t(NULL));


	Pipe p;
	bool isConnect = p.connect();

	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return p;
		}
	}
	return p;
}


// check if move is valid - square on board
bool isOnBoard(int srcRow, int srcCol, int destRow, int destCol)
{
	// check if source and destination positions are on the board
	if (srcRow < MIN_BOARD_ROWS || srcRow >= MAX_BOARD_ROWS || srcCol < MIN_BOARD_COLS || srcCol >= MAX_BOARD_COLS || destRow < MIN_BOARD_ROWS || destRow >= MAX_BOARD_ROWS || destCol < MIN_BOARD_COLS || destCol >= MAX_BOARD_COLS)
	{
		return false; // out of bounds
	}
}

// check if move is valid -  current player piece
bool isCurrentPlayerPieceOnSource(const std::vector<std::vector<Piece*>>& board,int srcRow, int srcCol, char currentPlayerColor)
{
	Piece* piece = board[srcRow][srcCol];

	// check if there is a piece and if it belongs to the current player
	return (piece != nullptr && piece->getColor() == currentPlayerColor);
}


// play func responsible to game loop
void play(Pipe& p,Manager& game)
{
	// get message from graphics
	char msgToGraphics[1024];
	string msgFromGraphics = p.getMessageFromGraphics();
	int currentPlayerTurn = game.GetTurn();

	while (msgFromGraphics != "quit")
	{
		std::string source = msgFromGraphics.substr(0, 2);
		std::string destination = msgFromGraphics.substr(2, 2); 


		int srcRow = 8 - (source[1] - '0'); 
		int srcCol = source[0] - 'a';
		int destRow = 8 - (destination[1] - '0');
		int destCol = destination[0] - 'a';

	    
		// check if the move is on the board 
		if (!(isOnBoard(srcRow, srcCol, destRow, destCol)))
		{
			strcpy_s(msgToGraphics, "YOUR CODE");
			int r = rand() % 10;
			msgToGraphics[0] = (char)(5 + '0');
			msgToGraphics[1] = 0;

			p.sendMessageToGraphics(msgToGraphics);

			// get message from graphics
			msgFromGraphics = p.getMessageFromGraphics();

			continue;
		}


		// check if there is no current players piece on the source square
		if (!(isCurrentPlayerPieceOnSource(game.GetBoardVector(), srcRow, srcCol, currentPlayerTurn)))
		{

			strcpy_s(msgToGraphics, "Invalid source square");


			msgToGraphics[0] = (char)(2 + '0'); 
			msgToGraphics[1] = '\0'; 

			// send the message to the graphics
			p.sendMessageToGraphics(msgToGraphics);

			// get a response from the graphics 
			msgFromGraphics = p.getMessageFromGraphics();

			continue;
		}


		strcpy_s(msgToGraphics, "YOUR CODE");

		int r = rand() % 10; 
		msgToGraphics[0] = (char)(0 + '0');
		msgToGraphics[1] = 0;


		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
		if (currentPlayerTurn == WHITE)
		{
			game.SetTurnBlack();
			currentPlayerTurn = game.GetTurn();
		}

		else if (currentPlayerTurn == BLACK)
		{
			game.SetTurnWhite();
			currentPlayerTurn = game.GetTurn();
		}


	}

	p.close();
}



void main()
{

	Manager game("rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0");
	Pipe p = connect();
	std::string board = game.GetStartingBoardStr();
	game.drawBoard(p,board);

	// gameloop
	play(p, game);
}