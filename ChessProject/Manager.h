#pragma once
#include <vector>
#include <string>
#include "Piece.h"

class Piece;

class Manager
{
private:
	std::vector<std::vector<Piece*>> _board;
	int _turn;

	Piece* createPiece(const char piece, const int color);

public:
	Manager(const std::string& board);
	~Manager();

	std::string GetBoard() const;
	int GetTurn() const;
	
	void SetBoard(const std::string& board);
	void SwitchTurn();

	void printBoard();
	void MoveBoard(std::string move);
};

