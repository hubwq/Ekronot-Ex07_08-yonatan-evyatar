#ifndef KING_H
#define KING_H

#include "King.h"


King::King(const int color) : Piece("King", color)
{
}

King::~King()
{
}

void King::Move(Manager& board, const std::string& move) const
{
    std::string boardstr = board.GetBoard();
    
    int sRow = '8' - move[1];
    int sCol = move[0] - 'a';
    int dRow = '8' - move[3];
    int dCol = move[2] - 'a';

    // calculate movement deltas
    int rowDelta = dRow - sRow;
    int colDelta = dCol - sCol;

    // valid queen movement
    if (abs(rowDelta) <= 1 && abs(colDelta) <= 1) 
    {
        throw MoveExeption("0\0");
    }
    else
    {
        throw MoveExeption("6\0");
    }
}
#endif // KING_H