#ifndef KING_H
#define KING_H

#include "King.h"


King::King(const int color) : Piece("King", color)
{
}

King::King(const int color, const bool moved) : Piece("King", color, moved)
{
}

King::~King()
{
}

void King::Move(Manager& board, const int sRow, const int sCol, const int dRow, const int dCol) const
{
    std::string boardstr = board.GetBoard();

    // calculate movement deltas
    int rowDelta = dRow - sRow;
    int colDelta = dCol - sCol;



    // valid queen movement
    if (abs(rowDelta) <= 1 && abs(colDelta) <= 1)
    {
        throw MoveExeption("0\0");
    }
    else if (isCastling(board, sRow, sCol, dRow, dCol))
    {
        // Handle castling logic here
        // Move the rook to the appropriate position
        int rookStartCol = (sCol < dCol) ? 7 : 0;
        int rookEndCol = (sCol < dCol) ? dCol - 1 : dCol + 1;

        // Update the board for castling
        board.MoveBoard(board.MoveToStr(sRow, rookStartCol, sRow, rookEndCol));

        // Indicate successful castling
        throw MoveExeption("0\0");
    }
    else
    {
        throw MoveExeption("6\0");
    }
}

/*
* Check if castling is possible
*/
bool King::isCastling(Manager& game, const int sRow, const int sCol, const int dRow, const int dCol) const
{
    std::vector<std::vector<Piece*>> board = game.GetBoardVector();

    // if its king that was not moved before and if the move is castling
    if (sRow == dRow && (sCol == dCol - 2 || sCol == dCol + 2) && this->getMoved() == false)
    {
        // Rook index
        const int rCol = (sCol - dCol < 0) ? 7 : 0;
        const Piece* rook = board[sRow][rCol];

        // if its a Rook that was not moved before
        if (rook != nullptr && rook->getName()[0] == 'R' && rook->getColor() == this->getColor() && rook->getMoved() == false)
        {
            // Determine the direction of the castling move
            const int colStep = (sCol < dCol) ? 1 : -1;

            // Check if all squares between the king and the rook are empty
            for (int col = sCol + colStep; col != rCol; col += colStep)
            {
                if (board[sRow][col] != nullptr)
                {
                    return false; // Path is not clear
                }
            }

            // Check if the king passes through or ends up in a check position
            for (int col = sCol; col != dCol + colStep; col += colStep)
            {
                // Simulate the king's move
                board[sRow][col] = const_cast<King*>(this);
                board[sRow][sCol] = nullptr;

                bool inCheck = game.isChess(this->getColor(), board);

                // Undo the simulated move
                board[sRow][sCol] = const_cast<King*>(this);
                board[sRow][col] = nullptr;

                if (inCheck)
                {
                    return false; // King would pass through or end in check
                }
            }

            return true;
        }
    }
    return false;
}
#endif // KING_H