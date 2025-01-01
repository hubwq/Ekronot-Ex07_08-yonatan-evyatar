#pragma once
#include <string>
#include "Piece.h"

class Queen : public Piece
{
public:
	Queen(const int color);
	~Queen();
	virtual void Move(const Manager& board, const std::string& move) const override;
};
