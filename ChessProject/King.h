#pragma once
#include <string>
#include <vector>
#include "Piece.h"

class King : public Piece
{
public:
	King(const int color);
	King(const int color, const bool moved);
	virtual ~King();
	virtual void Move(Manager& board, const int sRow, const int sCol, const int dRow, const int dCol) const override;
	bool isCastling(Manager& board, const int sRow, const int sCol, const int dRow, const int dCol) const;
};
