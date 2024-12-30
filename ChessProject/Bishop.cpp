#include "Bishop.h"

Bishop::Bishop(const int color)
	: Piece("Bishop", color)
{
}

Bishop::~Bishop()
{
}

void Bishop::Move(const Manager& board, const std::string& move) const
{
	MoveExeption error;

	if (error.checkMove(board.GetBoard(), board.GetTurn(), move))
	{
		
	}
	else
	{
		throw error;
	}
}