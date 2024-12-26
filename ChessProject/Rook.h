#pragma once
#include <string>
#include "Piece.h"

class Rook : public Piece
{

private:
	Piece* _Piece;
public:
	Rook(const std::string& name, int color);
	virtual ~Rook();
};
