#pragma once
#include <string>
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(const int color);
	virtual ~Pawn();
	virtual void Move(Manager& board, const int sRow, const int sCol, const int dRow, const int dCol) const override;
};
