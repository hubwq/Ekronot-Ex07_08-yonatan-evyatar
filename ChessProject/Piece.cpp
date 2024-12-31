#include "Piece.h"

Piece::Piece(const std::string name, const int color): _name(name), _color(color)
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