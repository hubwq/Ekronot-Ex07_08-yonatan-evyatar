#pragma once
#include <string>
#include "Piece.h"

class King : public Piece
{
public:
	King(const int color);
	virtual ~King();
	virtual void Move(Manager& board, const std::string& move) const override;
};
