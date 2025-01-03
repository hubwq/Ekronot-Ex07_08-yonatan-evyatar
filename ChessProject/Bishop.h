#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	Bishop(const int color);
	virtual ~Bishop();
	virtual void Move(Manager& board, const std::string& move) const override;
};

