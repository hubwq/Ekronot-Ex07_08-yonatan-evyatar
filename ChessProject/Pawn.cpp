#include "Pawn.h"

Pawn::Pawn(const int color) : Piece("Pawn", color)
{
}

Pawn::~Pawn()
{
}


void Pawn::Move(const Manager& board, const std::string& move) const
{
	std::string boardstr = board.GetBoard();

	if (move.length() == 4)
	{
		if ((move[0] >= 'a' && move[0] <= 'h') && (move[1] >= '1' || move[1] <= '8') && (move[2] >= 'a' && move[2] <= 'h') && (move[3] >= '1' || move[3] <= '8'))
		{
			int sourcRow = move[0] - 'a';
			int sourcCol = move[1] - '0';
			int destRow = move[2] - 'a';
			int destCol = move[3] - '0';
		}
	}
	else
	{
		throw MoveSizeExeption();
	}
}