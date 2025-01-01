#pragma once
#include <string>
#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(const int color);
	~Rook();
	virtual void Move(const Manager& board, const std::string& move) const override;
};
