#ifndef KNIGHT_H
#define KNIGHT_H

#include "Knight.h"


Knight::Knight(const int color): Piece("nKnight", color)
{
}

Knight::~Knight()
{
}

void Knight::Move(Manager& board, const std::string& move) const
{
	std::string boardstr = board.GetBoard();
	
	int sRow = '8' - move[1];
	int sCol = move[0] - 'a';
	int dRow = '8' - move[3];
	int dCol = move[2] - 'a';

	int rowOffset = abs(dRow - sRow);
	int colOffset = abs(dCol - sCol);

	// check if the dest is in L from the source
	if ((rowOffset == 2 && colOffset == 1) || (rowOffset == 1 && colOffset == 2))
	{
		// valid
		throw MoveExeption("0\0");
	}
	else
	{
		throw MoveExeption("6\0");
	}
}
#endif // KNIGHT_H