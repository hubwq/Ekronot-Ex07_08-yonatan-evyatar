#ifndef ROOK_H
#define ROOK_H
#include "Rook.h"

Rook::Rook(const int color) : Piece("Rook", color)
{
}

Rook::~Rook()
{
}


void Rook::Move(const Manager& board, const std::string& move) const
{
    std::string boardstr = board.GetBoard();
    MoveExeption error;

    // Check if the move is valid for any piece
    if (error.checkMove(boardstr, board.GetTurn(), move))
    {
        int sRow = '8' - move[1];
        int sCol = move[0] - 'a';
        int dRow = '8' - move[3];
        int dCol = move[2] - 'a';

        // check if the move is in a straight line
        if (sRow == dRow || sCol == dCol)
        {
            int rowStep = (dRow > sRow) ? 1 : (dRow < sRow ? -1 : 0); 
            int colStep = (dCol > sCol) ? 1 : (dCol < sCol ? -1 : 0); 

            int currentRow = sRow + rowStep;
            int currentCol = sCol + colStep;

            // check all squares between source and destination for obstacles
            while (currentRow != dRow || currentCol != dCol)
            {
                if (boardstr[currentRow * 8 + currentCol] != '#')
                {
                    throw MoveExeption("3\0"); 
                }
                currentRow += rowStep;
                currentCol += colStep;
            }

            // Move is valid for a rook
            throw MoveExeption("0\0");
        }
        else
        {
            throw MoveExeption("6\0");
        }
    }
    else
    {
        throw error;
    }
}

#endif // ROOK_H