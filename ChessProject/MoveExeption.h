#pragma once
#include <exception>
#include <string>
#include <vector>
#include "Piece.h"

class MoveExeption : public std::exception
{
private:
	const char* _errormsg;
	
public:
	MoveExeption();
	MoveExeption(const char* errorcode);
	~MoveExeption();

	bool checkMove(const std::string& board, const int playerColor, const std::string& move);

	const char* what() const noexcept override
	{
		return this->_errormsg;
	}
};

