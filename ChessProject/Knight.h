#pragma once
#include <string>
#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(const int color);
	virtual ~Knight();
	virtual void Move(Manager& board, const int sRow, const int sCol, const int dRow, const int dCol) const override;
};
