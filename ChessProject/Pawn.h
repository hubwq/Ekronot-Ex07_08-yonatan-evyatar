#pragma once
#include <string>
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(const int color);
	virtual ~Pawn();
	virtual void Move(Manager& board, const std::string& move) const override;
};
