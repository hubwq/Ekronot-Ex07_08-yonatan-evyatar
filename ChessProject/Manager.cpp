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

void Manager::changeBoardValue(const char piece, const int color, const int row, const int col)
{
	_board[row][col] = createPiece(piece, color);
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
		int sRow = '8' - move[1];
		int sCol = move[0] - 'a';
		int dRow = '8' - move[3];
		int dCol = move[2] - 'a';
		try
		{
			// Execute the move 
			this->_board[sRow][sCol]->Move(*this, move);
		}
		catch (MoveExeption e)
		{
			// If the move is legal
			if (e.what()[0] == '0')
			{
				Piece* srcPiece = _board[sRow][sCol];
				Piece* dstPiece = _board[dRow][dCol];
				std::string dstName = (dstPiece) ? dstPiece->getName() : "#";
				int dstColor = (dstPiece) ? dstPiece->getColor() : -1;
				// check if there is a piece to kill 
				if (_board[dRow][dCol] != nullptr)
				{
					// delete the piece at the target position
					delete _board[dRow][dCol];
					_board[dRow][dCol] = nullptr;
				}

				// move the piece to dest
				_board[dRow][dCol] = createPiece(srcPiece->getName()[0], srcPiece->getColor());

				// Reset 'lastDoubleMove' at the start of a new turn
				if (!(srcPiece->getName() == "Pawn" && std::abs(sRow - dRow) == 2))
				{
					this->lastDoubleMove = -1;
				}

				// delete the piece from source
				delete _board[sRow][sCol];
				_board[sRow][sCol] = nullptr;

				// Undo move if there is 'chess' on players king
				if (isChess(_turn))
				{
					_board[sRow][sCol] = createPiece(_board[dRow][dCol]->getName()[0], _board[dRow][dCol]->getColor());
					delete _board[dRow][dCol];
					_board[dRow][dCol] = nullptr;
					_board[dRow][dCol] = createPiece(dstName[0], dstColor);
					throw MoveExeption("4\0");
				}
				// check if there is 'chess' to opponent's king
				else if (isChess((_turn) ? 0 : 1))
				{
					if (isMate((_turn) ? 0 : 1))
					{
						throw MoveExeption("8\0");
					}
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

/*
* Check if there is CheckMate
* input: int - witch player gets the mate.
* output: if there is a mate to the player.
*/
bool Manager::isMate(int playerColor)
{
	// Check if the king is in check
	if (!isChess(playerColor))
	{
		return false; // No check, so no checkmate
	}

	// Iterate through all pieces of the given color
	for (int row = 0; row < 8; row++)
	{
		for (int col = 0; col < 8; col++)
		{
			Piece* piece = _board[row][col];
			if (piece && piece->getColor() == playerColor)
			{
				// Try all possible moves for this piece
				for (int dRow = 0; dRow < 8; dRow++)
				{
					for (int dCol = 0; dCol < 8; dCol++)
					{
						// Skip the same square
						if (dRow == row && dCol == col)
						{
							continue;
						}

						// Convert to move string
						char srcCol = 'a' + col;
						char srcRow = '8' - row;
						char dstCol = 'a' + dCol;
						char dstRow = '8' - dRow;
						std::string move = { srcCol, srcRow, dstCol, dstRow };

						// Try the move
						try
						{
							MoveExeption e;
							if (e.checkMove(GetBoard(), playerColor, move))
							{
								try
								{
									piece->Move(*this, move);
								}
								catch (MoveExeption e)
								{
									if (e.what()[0] == '0')
									{
										// Temporarily execute the move
										Piece* tempSrc = _board[row][col];
										Piece* tempDst = _board[dRow][dCol];
										_board[dRow][dCol] = tempSrc;
										_board[row][col] = nullptr;

										// Check if the king is still in check
										bool stillInCheck = isChess(playerColor);

										// Undo the move
										_board[row][col] = tempSrc;
										_board[dRow][dCol] = tempDst;

										// If the move gets the king out of check, no mate
										if (!stillInCheck)
										{
											return false;
										}
									}
								}

							}
						}
						catch (MoveExeption&)
						{
							// Invalid move, ignore and continue
						}
					}
				}
			}
		}
	}

	// If no valid moves are found, it's checkmate
	return true;
}
