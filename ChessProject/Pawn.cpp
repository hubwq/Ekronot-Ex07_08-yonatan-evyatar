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
void Pawn::Move(const Manager& board, const std::string& move) const
{
	std::string boardstr = board.GetBoard();
	MoveExeption error;

	const int SINGLE_STEP = (board.GetTurn() == 0) ? -1 : 1;
	const int DOUBLE_STEP = (board.GetTurn() == 0) ? -2 : 2;
	const int DIOGINAL = 1;

	int sRow = '8' - move[1];
	int sCol = move[0] - 'a';
	int dRow = '8' - move[3];
	int dCol = move[2] - 'a';

	if (dRow == sRow + SINGLE_STEP && sCol == dCol && boardstr[dRow * 8 + dCol] == '#')
	{
		throw MoveExeption("0\0");
	}

	else if (dRow == sRow + DOUBLE_STEP && sCol == dCol && boardstr[dRow * 8 + dCol] == '#' && ((board.GetTurn() == 0 && sRow == 6) || (board.GetTurn() == 1 && sRow == 1)))
	{
		throw MoveExeption("0\0");
	}

	// kill move dont working
	// check dioginal kill move
	else if (dRow == sRow + SINGLE_STEP && (dCol == sCol + DIOGINAL || dCol == sCol - DIOGINAL))
	{
		// if the dest square is not enemy piece
		if (boardstr[dRow * 8 + dCol] == '#')
		{
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


