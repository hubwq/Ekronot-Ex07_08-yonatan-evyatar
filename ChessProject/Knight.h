#pragma once
#include <string>
#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(const int color);
	virtual ~Knight();
	virtual void Move(const Manager& board, const std::string& move) const override;
};
