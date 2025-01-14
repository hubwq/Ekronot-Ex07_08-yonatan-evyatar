#pragma once
#include <string>
#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(const int color);
	Rook(const int color, const bool moved);
	~Rook();
	virtual void Move(Manager& board, const int sRow, const int sCol, const int dRow, const int dCol) const override;
};
