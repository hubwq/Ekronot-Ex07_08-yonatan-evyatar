#ifndef ROOK_H
#define ROOK_H
#include "Rook.h"

Rook::Rook(const int color) : Piece("Rook", color, false)
{
}

Rook::Rook(const int color, const bool moved) : Piece("Rook", color, moved)
{
}

Rook::~Rook()
{
}


void Rook::Move(Manager& board, const int sRow, const int sCol, const int dRow, const int dCol) const
{
    std::string boardstr = board.GetBoard();

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
                throw MoveExeption("6\0");
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

#endif // ROOK_H