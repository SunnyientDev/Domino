// Binds everything from Domino.cpp
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <list>
#include "domino.h"
#include "handling.h"
using namespace std;

class Game: public Handling {
public:
    list <Domino> stol;
    list <Domino> player1;
    list <Domino> player2;
    list <Domino> nobody; // stolen for private

    int Motion;
    int X; // stores the beginning of the output
    int Y; // stores the end of the output
    int loop; // prevents loops caused by the lack of dominoes in both players

    void WriteDomino (); // We write all the dominoes on the board
    void Lookfromthetable (Domino); // Go back one state
    int AddDomino (list <Domino>); // Adds penalty dominoes from the “no man” sheet when a player does not have suitable dominoes
    void MakeDomino (); // Distribute dominoes at the beginning of a new game
    int CheckMotion (list <Domino>); // Checks if the player can make a move
    void WriteUserBlocks (list <Domino>); // Updates the list of blocks (dominoes) after adding a new domino
    list <Domino> MakeMove (char [], list <Domino>); // Checks if the current player can make a move
    void CountPoints (); // Defines the winner in case of a tie
};
#endif
