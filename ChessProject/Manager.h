#pragma once
#include <vector>
#include <string>
#include "Piece.h"
#include "../Frontend/Pipe.h"

class Piece;

class Manager
{
private:
	std::vector<std::vector<Piece*>> _board;
	std::string _boardStr;
	int _turn;
	Piece* createPiece(const char piece, const int color);
	int lastDoubleMove;

public:
	Manager(const std::string& board);
	~Manager();
	std::string GetBoard() const;
	std::vector<std::vector<Piece*>> GetBoardVector();
	std::string GetStartingBoardStr() const;
	void drawBoard(Pipe& p, std::string& board);
	int GetTurn() const;
	
	void SetBoard(const std::string& board);
	void changeBoardValue(const char piece, const int color, const int row, const int col);

	void SwitchTurn();
	void MoveBoard(const std::string& move);
	int getLastDoubleMove();
	void setLastDoubleMove(int index);

	void promotion(int dRow, int sRow, int dCol, int sCol, int color);

	bool isChess(int playerColor);
	bool isChess(int playerColor, std::vector<std::vector<Piece*>> board);
	bool isMate(int playerColor);

	static std::string MoveToStr(const int sRow, const int sCol, const int dRow, const int dCol);
};

