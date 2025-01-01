#ifndef QUEEN_H
#define QUEEN_H

#include "Queen.h"

Queen::Queen(const int color) : Piece("Queen", color)
{
}

Queen::~Queen()
{
}


void Queen::Move(const Manager& board, const std::string& move) const 
{
    std::string boardstr = board.GetBoard();
    MoveExeption error;

    // check if the move is valid for any piece
    if (error.checkMove(boardstr, board.GetTurn(), move)) {
        int sRow = '8' - move[1];
        int sCol = move[0] - 'a';
        int dRow = '8' - move[3];
        int dCol = move[2] - 'a';

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
                    throw MoveExeption("3\0");
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
    else
    {
        throw error; // Forward the error from checkMove
    }
}

#endif // QUEEN_H