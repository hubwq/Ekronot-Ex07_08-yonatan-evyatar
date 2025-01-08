#ifndef PAWN_H
#define PAWN_H

#include "Pawn.h"
Pawn::Pawn(const int color) : Piece("Pawn", color)
{
}



Pawn::~Pawn()
{
}

// pawn move
void Pawn::Move(Manager& board, const std::string& move) const
{
	std::string boardstr = board.GetBoard();
	MoveExeption error;

	const int SINGLE_STEP = (getColor() == 0) ? -1 : 1;
	const int DOUBLE_STEP = (getColor() == 0) ? -2 : 2;
	const int DIOGINAL = 1;
	int sRow = '8' - move[1];
	int sCol = move[0] - 'a';
	int dRow = '8' - move[3];
	int dCol = move[2] - 'a';

	// normal move
	if (dRow == sRow + SINGLE_STEP && sCol == dCol && boardstr[dRow * 8 + dCol] == '#')
	{
		throw MoveExeption("0\0");
	}

	// double move
	else if (dRow == sRow + DOUBLE_STEP && sCol == dCol && boardstr[dRow * 8 + dCol] == '#' && ((board.GetTurn() == 0 && sRow == 6) || (board.GetTurn() == 1 && sRow == 1)))
	{
		board.setLastDoubleMove((dRow - SINGLE_STEP) * 8 + dCol);
		throw MoveExeption("0\0");
	}


	// dioginal capture move
	else if (dRow == sRow + SINGLE_STEP && (dCol == sCol + DIOGINAL || dCol == sCol - DIOGINAL))
	{
		// if the dest square is not enemy piece
		if (boardstr[dRow * 8 + dCol] == '#')
		{
			if ((board.getLastDoubleMove() >= 0 && board.getLastDoubleMove() < 64) && (dRow * 8 + dCol) == board.getLastDoubleMove())
			{
				Piece* piece = board.GetBoardVector()[sRow][dCol];
				// Remove the captured pawn
				delete piece;
				board.changeBoardValue('#', -1, sRow, dCol);
				throw MoveExeption("0\0");

			}
			throw MoveExeption("6\0");
		}
		throw MoveExeption("0\0");
	}

	else
	{
		throw MoveExeption("6\0");
	}
}


#endif // PAWN_H