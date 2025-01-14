#pragma once
#include <string>
#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(const int color);
	~Queen();
	virtual void Move(Manager& board, const int sRow, const int sCol, const int dRow, const int dCol) const override;
};
