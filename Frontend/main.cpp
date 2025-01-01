#include "../Frontend/Pipe.h"
#include <iostream>
#include <thread>
#include "Manager.h"

using std::cout;
using std::endl;
using std::string;


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



// check if the move is from place and to place inside board bound
void drawBoard(Pipe& p ,std::string& board)
{
	char msgToGraphics[1024];


	strcpy_s(msgToGraphics, board.c_str());
	p.sendMessageToGraphics(msgToGraphics);   // send the board string
}



bool isOnBoard(int srcRow, int srcCol, int destRow, int destCol)
{
	// Check if source and destination positions are on the board
	if (srcRow < MIN_BOARD_ROWS || srcRow >= MAX_BOARD_ROWS || srcCol < MIN_BOARD_COLS || srcCol >= MAX_BOARD_COLS || destRow < MIN_BOARD_ROWS || destRow >= MAX_BOARD_ROWS || destCol < MIN_BOARD_COLS || destCol >= MAX_BOARD_COLS)
	{
		return false; // out of bounds
	}
}


bool isCurrentPlayerPieceOnSource(const std::vector<std::vector<Piece*>>& board,
	int srcRow, int srcCol, char currentPlayerColor)
{
	// Check if the source position is valid and within the board bound
	if (srcRow < MIN_BOARD_ROWS || srcRow >= MAX_BOARD_ROWS || srcCol < MIN_BOARD_COLS || srcCol >= MAX_BOARD_COLS)
		return false;

	// het the piece at the source position
	Piece* piece = board[srcRow][srcCol];

	// Check if there is a piece and if it belongs to the current player
	if (piece != nullptr && piece->getColor() == currentPlayerColor)
	{
		return true;
	}

	return false;
}



void play(Pipe p,Manager game)
{
	// get message from graphics
	char msgToGraphics[1024];
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		std::string source = msgFromGraphics.substr(0, 2);
		std::string destination = msgFromGraphics.substr(2, 2); 
		std::vector<std::vector<Piece*>> _board;

		int srcRow = 8 - (source[1] - '0'); 
		int srcCol = source[0] - 'a';
		int destRow = 8 - (destination[1] - '0');
		int destCol = destination[0] - 'a';
		int currentPlayerTurn = game.GetTurn();

		// check if there an current player piece on source square

		if (isCurrentPlayerPieceOnSource(_board, srcRow, srcCol, currentPlayerTurn))
		{
			strcpy_s(msgToGraphics, "YOUR CODE");

			int r = rand() % 10;
			msgToGraphics[0] = (char)(2 + '0');
			msgToGraphics[1] = 0;

		}

		// check if the move is on the board 
		if (isOnBoard(srcRow, srcCol, destRow, destCol))
		{
			strcpy_s(msgToGraphics, "YOUR CODE");

			int r = rand() % 10; 
			msgToGraphics[0] = (char)(5 + '0');
			msgToGraphics[1] = 0;


		}

		strcpy_s(msgToGraphics, "YOUR CODE");

		/******* JUST FOR EREZ DEBUGGING ******/
		int r = rand() % 10; // just for debugging......
		msgToGraphics[0] = (char)(1 + '0');
		msgToGraphics[1] = 0;
		/******* JUST FOR EREZ DEBUGGING ******/


		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}



void main()
{

	Manager game("rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR1");
	Pipe p = connect();
	std::string board = game.GetBoard(); //error to draw board fix it
	drawBoard(p,board);
	// gameloop
	play(p, game);
}