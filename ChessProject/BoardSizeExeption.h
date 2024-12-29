#pragma once
#include <exception>

class BoardSizeExeption : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Invalid board size\n";
	}
};

