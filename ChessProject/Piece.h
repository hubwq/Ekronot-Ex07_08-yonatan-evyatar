#pragma once
#include <string>

class Piece
{
protected:
	std::string _name;
	int _color;

public:
	Piece(const std::string& name, int color);
	virtual ~Piece();

	std::string getName() const;
	int getColor() const;

	virtual void Move(std::string&) const = 0;
};

