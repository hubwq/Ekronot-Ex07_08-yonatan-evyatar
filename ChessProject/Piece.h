#pragma once
#include <string>
#include "Manager.h"
#include "MoveExeption.h"

class Manager;

class Piece
{
private:
	std::string _name;
	int _color;

public:
	Piece(const std::string name, const int color);
	virtual ~Piece();

	std::string getName() const;
	int getColor() const;

	virtual void Move(Manager& board, const std::string& move) const = 0;
};

