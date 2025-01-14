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
	bool _moved; //if the piece was moved; need for castling.

public:
	Piece(const std::string name, const int color);
	Piece(const std::string name, const int color, const bool moved);
	virtual ~Piece();

	std::string getName() const;
	int getColor() const;
	bool getMoved() const;

	void setMoved(const bool moved);

	virtual void Move(Manager& board, const int sRow, const int sCol, const int dRow, const int dCol) const = 0;
};

