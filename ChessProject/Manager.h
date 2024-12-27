#pragma once
#include <vector>
#include "Piece.h"
#include "../Frontend/Pipe.h"
class Manager
{
private:
	std::vector<std::vector<Piece*>> _board;
	int _turn;
	Pipe _p;

public:
	Manager();
	~Manager();
	void connectToFront();
	std::string getBoard();
	
	void SetBoard();
};

