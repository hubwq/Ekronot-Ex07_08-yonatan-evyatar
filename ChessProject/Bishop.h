#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(const int color);
	virtual ~Bishop();
	virtual void Move(Manager& board, const int sRow, const int sCol, const int dRow, const int dCol) const override;
};

