#include "../Frontend/Pipe.h"
#include <iostream>
#include <thread>
#include "Piece.h"
#include "Manager.h"

using std::cout;
using std::endl;
using std::string;

#define WHITE 0
#define BLACK 1
#define MAX_BOARD_ROWS 8
#define MAX_BOARD_COLS 8
#define MIN_BOARD_ROWS 0
#define MIN_BOARD_COLS 0

// FOR DEBUG - DONT SHOW PIECES TYPE ONLY PIECES COLOR
void printBoard(const std::vector<std::vector<Piece*>>& board)
{
    cout << "Board state:" << endl;
    for (int row = 0; row < MAX_BOARD_ROWS; ++row)
    {
        for (int col = 0; col < MAX_BOARD_COLS; ++col)
        {
            Piece* piece = board[row][col];
            if (piece != nullptr)
                cout << piece->getColor() << " "; // Assuming `getSymbol()` gives the piece symbol
            else
                cout << ". "; // Empty square
        }
        cout << endl;
    }
}

// Connect to pipe
Pipe connect()
{
    srand(time_t(NULL));

    Pipe p;
    bool isConnect = p.connect();

    string ans;
    while (!isConnect)
    {
        cout << "Can't connect to graphics" << endl;
        cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
        std::cin >> ans;

        if (ans == "0")
        {
            cout << "Trying to connect again..." << endl;
            Sleep(5000);
            isConnect = p.connect();
        }
        else
        {
            p.close();
            return p;
        }
    }
    return p;
}

// check if move is valid - square on board
bool isOnBoard(int srcRow, int srcCol, int destRow, int destCol)
{
    if (srcRow < MIN_BOARD_ROWS || srcRow >= MAX_BOARD_ROWS ||
        srcCol < MIN_BOARD_COLS || srcCol >= MAX_BOARD_COLS ||
        destRow < MIN_BOARD_ROWS || destRow >= MAX_BOARD_ROWS ||
        destCol < MIN_BOARD_COLS || destCol >= MAX_BOARD_COLS)
    {
        return false; 
    }
    return true; 
}

// check if the current player has a piece on the source square
bool isCurrentPlayerPieceOnSource(const std::vector<std::vector<Piece*>>& board, int srcRow, int srcCol, int currentPlayerColor)
{
    Piece* piece = board[srcRow][srcCol];

    // check if there is a piece and if it belongs to the current player
    return (piece != nullptr && piece->getColor() == currentPlayerColor);
}




// play function responsible for the game loop
void play(Pipe& p, Manager& game)
{
    // get message from graphics
    char msgToGraphics[1024];
    string msgFromGraphics = p.getMessageFromGraphics();

    while (msgFromGraphics != "quit")
    {
        int currentPlayerTurn = game.GetTurn();
        std::string source = msgFromGraphics.substr(0, 2);
        std::string destination = msgFromGraphics.substr(2, 2);
        std::vector<std::vector<Piece*>> board = game.GetBoardVector();
        std::string move = msgFromGraphics.substr(0, 4);



        int srcRow = 8 - (source[1] - '0');
        int srcCol = source[0] - 'a';
        int destRow = 8 - (destination[1] - '0');
        int destCol = destination[0] - 'a';

        // check if the move is on the board
        if (!(isOnBoard(srcRow, srcCol, destRow, destCol)))
        {
            strcpy_s(msgToGraphics, "Invalid move: out of bounds");
            msgToGraphics[0] = (char)(2 + '0'); 
            msgToGraphics[1] = '\0';

            p.sendMessageToGraphics(msgToGraphics);

            // get message from graphics
            msgFromGraphics = p.getMessageFromGraphics();

            continue;
        }

        // check if there is no current player's piece on the source square
        if (!(isCurrentPlayerPieceOnSource(board, srcRow, srcCol, currentPlayerTurn)))
        {
            strcpy_s(msgToGraphics, "Invalid source square");
            msgToGraphics[0] = (char)(2 + '0'); 
            msgToGraphics[1] = '\0';

            p.sendMessageToGraphics(msgToGraphics);

            // get a response from the graphics 
            msgFromGraphics = p.getMessageFromGraphics();

            continue;
        }

        if ( srcRow == destRow && srcCol == destCol)
        {
            strcpy_s(msgToGraphics, "source square and destination are equal");
            msgToGraphics[0] = (char)(7 + '0');
            msgToGraphics[1] = '\0';

            p.sendMessageToGraphics(msgToGraphics);

            // get a response from the graphics 
            msgFromGraphics = p.getMessageFromGraphics();

            continue;
        }


        //////////////////////////////////////////////////////////
        // move piece
        try
        {
            game.MoveBoard(move);
        }
        catch (MoveExeption e)
        {
            printBoard(board);
            // send move to graphics
            strcpy_s(msgToGraphics, "Move successful");
            msgToGraphics[0] = e.what()[0];
            msgToGraphics[1] = 0;
        }

        p.sendMessageToGraphics(msgToGraphics);

        if (msgToGraphics[0] == '0' || msgToGraphics[0] == '1')
        {
            game.SwitchTurn();
        }

        // get message from graphics
        msgFromGraphics = p.getMessageFromGraphics();

        //////////////////////////////////////////////////////////

    }

    p.close();
}






//**main function**
///////////////////
///////////////////

int main()
{
    Manager game("rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0");
    // connect to front
    Pipe p = connect();

    std::string board = game.GetStartingBoardStr();

    game.drawBoard(p, board);

    // game loop
    play(p, game);

    //do checkmate screen here?

    return 0;
}
