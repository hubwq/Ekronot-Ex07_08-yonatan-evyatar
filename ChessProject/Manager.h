#pragma once
#include <vector>
#include "Piece.h"

class Manager
{
private:
	std::vector<std::vector<Piece*>> _board;
	int _turn;

public:
	Manager();
	~Manager();

	std::string getBoard();
	
	void setBoard(std::string board);
};

