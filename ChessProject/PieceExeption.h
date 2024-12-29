#pragma once
#include <exception>

class PieceExeption : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Unknown piece character\n";
	}
};

