#include "Piece.h"

Piece::Piece(const std::string name, const int color) : _name(name), _color(color), _moved(false)
{
}

Piece::Piece(const std::string name, const int color, const bool moved) : _name(name), _color(color), _moved(moved)
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

bool Piece::getMoved() const
{
	return this->_moved;
}

void Piece::setMoved(const bool moved)
{
	this->_moved = moved;
}
