#pragma once
#include <string>
#include "Piece.h"

class Knight : public Piece
{

private:
	Piece* _Piece;
public:
	Knight(const std::string& name, int color);
	virtual ~Knight();
};
