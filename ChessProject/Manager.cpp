#include "Manager.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "BoardSizeExeption.h"
#include "PieceExeption.h"
#include <iostream>

Piece* Manager::createPiece(const char piece, const int color)
{
	switch (tolower(piece))
	{
	case 'r':
		return new Rook(color);
	case 'n':
		return new Knight(color);
	case 'b':
		return new Bishop(color);
	case 'k':
		return new King(color);
	case 'q':
		return new Queen(color);
	case 'p':
		return new Pawn(color);
	default:
		throw PieceExeption();
	}
}

/*
* Manager Constracor.
* Set a chess starting board
* and set who make first move.
*/
Manager::Manager(const std::string& board) : _turn(int(board[64] - '0') ? 1 : 0)
{
	if (board.length() != 65)
	{
		throw BoardSizeExeption();
	}

	_board.resize(8, std::vector<Piece*>(8, nullptr));

	SetBoard(board);
}


Manager::~Manager()
{
	for (auto& row : _board)
	{
		for (Piece* piece : row)
		{
			delete piece;
		}
	}
}

std::string Manager::GetBoard() const
{
	std::string board = "";

	for (int i = 0; i < 64; i++)
	{
		int row = i / 8;
		int col = i % 8;

		if (_board[row][col] != nullptr)
		{
			board += _board[row][col]->getName()[0];
			board[i] = (_board[row][col]->getColor()) ? tolower(board[i]) : toupper(board[i]);
		}
		else
		{
			board += '#';
		}
	}

	return board;
}


int Manager::GetTurn() const
{
	return this->_turn;
}


void Manager::SetBoard(const std::string& board)
{
	for (int i = 0; i < 64; i++)
	{
		int row = i / 8;
		int col = i % 8;
		char piece = board[i];

		if (_board[row][col] != nullptr) {
			delete _board[row][col];
			_board[row][col] = nullptr;
		}

		if (piece != '#')
		{
			int color = isupper(piece) ? 0 : 1; // Upparcase = white, Lowercase = black
			_board[row][col] = createPiece(piece, color);
		}
	}
}

void Manager::SwitchTurn()
{
	this->_turn = this->_turn ? 0 : 1;
}

void Manager::printBoard()
{
	std::string board = this->GetBoard();

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			std::cout << board[i * 8 + j] << ' ';
		}
		std::cout << board[i*8 + 7] << '\n';
	}
}

void Manager::MoveBoard(std::string move)
{
	MoveExeption error;
	if (error.checkMove(this->GetBoard(), this->_turn, move))
	{
		this->_board['8' - move[1]][move[0] - 'a']->Move(*this, move);
	}
	else
	{
		throw error;
	}
}
