#pragma once
#include <string>

class Piece
{
private:
	std::string _name;
	int _color;

public:
	Piece(std::string name, int color);
	virtual ~Piece();

	std::string getName() const;
	int getColor() const;

	virtual void Move(std::string) const = 0;
};

