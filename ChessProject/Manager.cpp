#include "Manager.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "BoardSizeExeption.h"
#include "PieceExeption.h"
#include "MoveExeption.h"

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
		return nullptr;
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
	_boardStr = board;
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

// not return a good board
std::string Manager::GetBoard() const
{
	std::string board = "";
	// iterate over all 64 squares
	for (int i = 0; i < 64; i++)
	{
		int row = i / 8;
		int col = i % 8;

		// vheck if there is a piece at the current square
		if (_board[row][col] != nullptr)
		{ 
			// g  et the first character of the pieces name
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

std::vector<std::vector<Piece*>> Manager::GetBoardVector()
{
	return _board;
}


std::string Manager::GetStartingBoardStr() const
{
	return _boardStr;
}

// check if the move is from place and to place inside board bound
void Manager::drawBoard(Pipe& p, std::string& board)
{
	char msgToGraphics[1024];


	strcpy_s(msgToGraphics, board.c_str());
	p.sendMessageToGraphics(msgToGraphics);   // send the board string
}



int Manager::GetTurn() const
{
	return this->_turn;
}


void Manager::SetBoard(const std::string& board)
{
	// iterate over all 64 squares
	for (int i = 0; i < 64; i++)
	{
		int row = i / 8; 
		int col = i % 8;  

		char piece = board[i];

		// if there is an existing piece at the current square
		if (_board[row][col] != nullptr)
		{
			delete _board[row][col];
			_board[row][col] = nullptr;
		}

		// if the square is not empty - '#'
		if (piece != '#')
		{
			// determine the color of the piece
			int color = isupper(piece) ? 0 : 1;

			// create the new piece 
			_board[row][col] = createPiece(piece, color);
		}
	}
}


void Manager::SwitchTurn()
{
	this->_turn = this->_turn ? 0 : 1;
}

void Manager::MoveBoard(const std::string& move)
{
	MoveExeption error;

	// validate the move using the current board state and turn
	if (error.checkMove(this->GetBoard(), this->_turn, move))
	{
		try
		{
			// Execute the move 
			this->_board['8' - move[1]][move[0] - 'a']->Move(*this, move);
		}
		catch (MoveExeption e)
		{
			// If the move is legal
			if (e.what()[0] == '0')
			{
				Piece* srcPiece = _board['8' - move[1]][move[0] - 'a'];
				Piece* dstPiece = _board['8' - move[3]][move[2] - 'a'];
				std::string dstName = (dstPiece) ? dstPiece->getName() : "#";
				int dstColor = (dstPiece) ? dstPiece->getColor() : -1;
				// check if there is a piece to kill 
				if (_board['8' - move[3]][move[2] - 'a'] != nullptr)
				{
					// delete the piece at the target position
					delete _board['8' - move[3]][move[2] - 'a'];
					_board['8' - move[3]][move[2] - 'a'] = nullptr;
				}

				// move the piece to dest
				_board['8' - move[3]][move[2] - 'a'] = createPiece(srcPiece->getName()[0], srcPiece->getColor());

				// delete the piece from source
				delete _board['8' - move[1]][move[0] - 'a'];
				_board['8' - move[1]][move[0] - 'a'] = nullptr;

				// Undo move if there is 'chess' on players king
				if (isChess(_turn))
				{
					_board['8' - move[1]][move[0] - 'a'] = createPiece(_board['8' - move[3]][move[2] - 'a']->getName()[0], _board['8' - move[3]][move[2] - 'a']->getColor());
					delete _board['8' - move[3]][move[2] - 'a'];
					_board['8' - move[3]][move[2] - 'a'] = nullptr;
					_board['8' - move[3]][move[2] - 'a'] = createPiece(dstName[0], dstColor);
					throw MoveExeption("4\0");
				}
				// check if there is 'chess' to opponent's king
				else if (isChess((_turn) ? 0 : 1))
				{
					throw MoveExeption("1\0");
				}
			}

			throw e;
		}
	}
	else
	{

		throw error;
	}
}


int Manager::getLastDoubleMove()
{
	return this->lastDoubleMove;
}

void Manager::setLastDoubleMove(int index)
{
	this->lastDoubleMove = index;
}

/*
* check if the king is in chess
* true  - in chess
* false - no chess
*/
bool Manager::isChess(int playerColor)
{
	int kingRow = -1, kingCol = -1;

	// find king position
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			Piece* piece = _board[row][col];
			if (piece && piece->getName() == "King" && piece->getColor() == playerColor)
			{
				kingRow = row;
				kingCol = col;

				break;
			}
		}
		if (kingRow != -1)
		{
			break;
		}
	}

	// if no king, there is no chess
	if (kingRow == -1 || kingCol == -1)
	{
		return false;
	}

	char kingColChr = ('a' + kingCol);
	char kingRowChr = ('8' - kingRow);
	std::string kingPosition = { kingColChr, kingRowChr };

	// check every opponent's piece on the board
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			Piece* piece = _board[row][col];
			if (piece && piece->getColor() != playerColor)
			{
				char pieceColChr = ('a' + col);
				char pieceRowChr = ('8' - row);
				std::string piecePosition = { pieceColChr , pieceRowChr };

				std::string move = piecePosition + kingPosition;

				// check if the piece do chess to the king
				try
				{
					MoveExeption e;
					if(e.checkMove(this->GetBoard(), (playerColor) ? 0 : 1, move))
						_board[row][col]->Move(*this, move);
					throw e;
				}
				catch (MoveExeption e)
				{
					if (e.what()[0] == '0')
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}
