#ifndef BISHOP_H
#define BISHOP_H

#include "Bishop.h"
#include <cmath>

Bishop::Bishop(const int color)
	: Piece("Bishop", color)
{
}

Bishop::~Bishop()
{
}

void Bishop::Move(Manager& board, const std::string& move) const
{
	std::string boardstr = board.GetBoard();

	int sRow = '8' - move[1];
	int sCol = move[0] - 'a';
	int dRow = '8' - move[3];
	int dCol = move[2] - 'a';
	// check if the dest is in dioginal from the source
	if (abs(sCol - dCol) == abs(sRow - dRow))
	{
		int rowStep = (dRow > sRow) ? 1 : -1;
		int colStep = (dCol > sCol) ? 1 : -1;

		int currentRow = sRow + rowStep;
		int currentCol = sCol + colStep;

		while (currentRow != dRow && currentCol != dCol) 
		{
			if (boardstr[currentRow * 8 + currentCol] != '#') 
			{
				throw MoveExeption("6\0");
			}
			currentRow += rowStep;
			currentCol += colStep;
		}
		// valid
		throw MoveExeption("0\0");
	}
	else
	{
		throw MoveExeption("6\0");
	}
}

#endif // BISHOP_H