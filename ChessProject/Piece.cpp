#include "Piece.h"

Piece::Piece(std::string name, int color)
	: _name(name), _color(color)
{
}

Piece::~Piece()
{
}

std::string Piece::getName() const
{
	return this->_name;
}

int Piece::getColor() const
{
	return this->_color;
}
