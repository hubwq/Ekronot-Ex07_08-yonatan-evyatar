#include "MoveExeption.h"

MoveExeption::MoveExeption()
{
}

MoveExeption::MoveExeption(const char* errorcode)
	: _errormsg(errorcode)
{
}

MoveExeption::~MoveExeption()
{
}

/*
* Do the check that is the
* same for all pieces.
* 
* True - Good move / Pass basic move test
* False - Bad move
*/
bool MoveExeption::checkMove(const std::string & board, const int playerColor, const std::string& move)
{
	// Move size
	if (move.length() == 4)
	{
		char srcRow = move[1];
		char srcCol = move[0];
		char dstRow = move[3];
		char dstCol = move[2];
		
		// Legal move format
		if ((srcCol >= 'a' && srcCol <= 'h') && (srcRow >= '1' || srcRow <= '8') && (dstCol >= 'a' && dstCol <= 'h') && (dstRow >= '1' || dstRow <= '8'))
		{
			int sRow = '8' - srcRow;
			int sCol = srcCol - 'a';
			int dRow = '8' - dstRow;
			int dCol = dstCol - 'a';
			// Source is legal
			if (board[sRow * 8 + sCol] != '#' && bool(islower(board[sRow * 8 + sCol])) == bool(playerColor))
			{
				// Dest is legal
				if (board[dRow * 8 + dCol] == '#' || bool(islower(board[dRow * 8 + dCol])) != bool(playerColor))
				{
					return true;
				}
				else
				{
					this->_errormsg = "3\0";
				}
			}
			else
			{
				this->_errormsg = "2\0";
			}
		}
		else
		{
			this->_errormsg = "7\0";
		}	
	}
	else
	{
		this->_errormsg = "Invalid move size\n";
	}

	return false;
}
