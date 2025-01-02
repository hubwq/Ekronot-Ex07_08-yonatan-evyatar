#ifndef PAWN_H
#define PAWN_H

#include "Pawn.h"
#define DIOGINAL 1

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

	if (error.checkMove(boardstr, board.GetTurn(), move))
	{
		int sRow = '8' - move[1];
		int sCol = move[0] - 'a';
		int dRow = '8' - move[3];
		int dCol = move[2] - 'a';

		int rowStep = (board.GetTurn() == 0) ? 1 : -1;

		// check normal move
		if (sRow == dRow + rowStep && sCol == dCol && boardstr[dRow * 8 + dCol] == '#')
		{

			throw MoveExeption("0\0");
		}

		// check dioginal eat move
		else if (sRow == dRow + rowStep && (sCol == dCol + DIOGINAL || sCol == dCol - DIOGINAL))
		{
			// if the dest square is not enemy piece
			if(boardstr[dRow * 8 + dCol] == '#')
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
	else
	{
		throw MoveExeption("6\0");
	}
}
#endif // PAWN_H