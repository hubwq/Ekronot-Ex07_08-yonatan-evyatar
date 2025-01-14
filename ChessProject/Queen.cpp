#ifndef QUEEN_H
#define QUEEN_H

#include "Queen.h"

Queen::Queen(const int color) : Piece("Queen", color)
{
}

Queen::~Queen()
{
}


void Queen::Move(Manager& board, const int sRow, const int sCol, const int dRow, const int dCol) const
{
    std::string boardstr = board.GetBoard();

    // calculate movement deltas
    int rowDelta = dRow - sRow;
    int colDelta = dCol - sCol;

    // valid queen movement
    if (abs(rowDelta) == abs(colDelta) || rowDelta == 0 || colDelta == 0)
    {
        int rowStep = (rowDelta == 0) ? 0 : (rowDelta > 0 ? 1 : -1);
        int colStep = (colDelta == 0) ? 0 : (colDelta > 0 ? 1 : -1);

        int currentRow = sRow + rowStep;
        int currentCol = sCol + colStep;


        while (currentRow != dRow || currentCol != dCol)
        {
            if (boardstr[currentRow * 8 + currentCol] != '#')
            {
                throw MoveExeption("6\0");
            }
            currentRow += rowStep;
            currentCol += colStep;
        }
        throw MoveExeption("0\0");
    }
    else
    {
        throw MoveExeption("6\0");
    }
}

#endif // QUEEN_H