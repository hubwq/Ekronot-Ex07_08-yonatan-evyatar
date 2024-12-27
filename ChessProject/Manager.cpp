#include "Manager.h"
#include <iostream>
#include <thread>
#include <chrono>

using std::cout;
using std::endl;
using std::string;

/*
 * Manager Constructor.
 * Sets the classic chess starting board
 * and initializes the turn to white.
 */
Manager::Manager() : _turn(0)
{
}

Manager::~Manager() 
{
}

void Manager::connectToFront()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    Pipe p;
    bool isConnect = p.connect();

    while (!isConnect)
    {
        cout << "Cannot connect to graphics." << endl;
        cout << "Do you want to try connecting again or exit? (0 - try again, 1 - exit): ";
        string ans;
        std::cin >> ans;

        if (ans == "0")
        {
            cout << "Attempting to reconnect..." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
            isConnect = p.connect();
        }
        else
        {
            p.close();
            return;
        }
    }

    cout << "Successfully connected to graphics." << endl;
}

void Manager::SetBoard()
{
    char msgToGraphics[1024];

    // Populate msgToGraphics with the board string according to the protocol.
    // Example: Setting up a standard chessboard.
    strcpy_s(msgToGraphics, "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR1");

    Pipe p;
    p.sendMessageToGraphics(msgToGraphics); // Send the board string.

    // Get a message from graphics.
    string msgFromGraphics = p.getMessageFromGraphics();

    while (msgFromGraphics != "quit")
    {
        // Handle the string sent from graphics according to the protocol.
        // Example input: e2e4 (move piece from e2 to e4).
        
        // YOUR CODE: Process the move and update the board state.

        // Placeholder for response to graphics.
        strcpy_s(msgToGraphics, "1"); // Example response: Success status.

        // Send the result back to graphics.
        p.sendMessageToGraphics(msgToGraphics);

        // Get the next message from graphics.
        msgFromGraphics = p.getMessageFromGraphics();
    }

    p.close();
}
