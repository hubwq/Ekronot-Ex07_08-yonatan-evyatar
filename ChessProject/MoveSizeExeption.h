#pragma once
#include <exception>

class MoveSizeExeption : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Invalid move size\n";
	}
};

