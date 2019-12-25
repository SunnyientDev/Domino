#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
  #include <utility>
  #include "game.h"
  #include <time.h>
using namespace std;

// Create changing lists for each player. Used in the main function only once when starting a new game.
void Game :: MakeDomino () {
    int loc; // location
    int x = 0;

    for (int i = 0; i <= 6; i ++) {
        for (int j = x; j <= 6; j ++) {
            loc = rand ()% 3; // 0,1,2 !!
            
            switch (loc) {
              case 0: {
                  if (player1.size () <7) {
                      Domino temp1 = Domino (i, j);
                      player1.push_back (temp1);}
                  else if (nobody.size () <14) {// if it weren’t, there would be too few blocks
                      Domino temp3 = Domino (i, j);
                      nobody.push_back (temp3);}
                  break;
              }
              
              case 1: {
                  if (player2.size () <7) {
                      Domino temp2 = Domino (i, j);
                      player2.push_back (temp2);}
                  else if (player1.size () <7) {// if there weren’t, there would be too few blocks
                      Domino temp1 = Domino (i, j);
                      player1.push_back (temp1);}
                  break;
              }
              
              case 2: {
                  if (nobody.size () <14) {
                      Domino temp3 = Domino (i, j);
                      nobody.push_back (temp3);}
                  else if (player2.size () <7) {
                      Domino temp2 = Domino (i, j);
                      player2.push_back (temp2);}
                  break;
              }
          }
        }
        x ++;
    }

    x = rand ()% 14;
     // The first block thrown into the table is random
    list <Domino> :: iterator iter; iter = nobody.begin ();
    for (; x> 0; x--) iter ++;
    Domino start = Domino (iter -> A, iter -> B);
    stol.push_back (start); // put the first domino on the table
    X = iter -> A; Y = iter -> B;
    nobody.erase (iter); // remove them from someone else's list
}

// Adds penalty dominoes from the “no owner” sheet when a player has no matching dominoes
int Game :: AddDomino (list <Domino> list_player) {
    bool take = 0; // Domino identifier

    if (nobody.size () <1) {// If there are no more blocks
        cout << "\ n Dominoes ended in the bazaar. The game is over. \ n";
        setPlay (false); // End the game :(
        return 0; }

    while ((nobody.size ()> 0) && (take == 0)) {// if there are chips in the bazaar and he can make a move (After all, a chip that does not fit can come across)
        list <Domino> :: iterator iter; iter = nobody.begin ();
        Domino temp2 = Domino (iter -> A, iter -> B); // You can write simply as A, B. Just so more correctly
        list_player.push_back (temp2); // give dominoes to the player
        nobody.erase (iter); // Remove the domino from the nobody list

        printf ("Player% d received: [% d |% d]. \ n", Motion, iter -> A, iter -> B);
        list <Domino> :: iterator temp;

        for (temp = list_player.begin (); temp! = list_player.end (); temp ++)
            if ((temp-> A == X) || (temp-> B == X) || (temp-> A == Y) || (temp-> B == Y)) take = 1; // If We Can Make A Move!
       (Motion == 1)? (player1 = list_player): (player2 = list_player);
    }
    return 1;
}

 // Checks if the player can make a move. If not, it calls the function to add dominoes
int Game :: CheckMotion (list <Domino> list_player) {
list <Domino> :: iterator temp;
for (temp = list_player.begin (); temp! = list_player.end (); temp ++) {// We can make a move
        if ((temp-> A == X) || (temp-> A == Y) || (temp-> B == Y) || (temp-> B == X)) {loop = 0; return 1; }
}
  
  cout << "\ n Player" << Motion << "cannot make a move. \ n";
  if (nobody.size ()> 0) {AddDomino (list_player); return 1; }
    else {
        cout << "\ n There are no free chips for the player. \ n";
if (Motion == 1 && loop == 0) loop = 1;
        else if (Motion == 2 && loop == 0) loop = 2;
        else if (((Motion == 2 && loop == 1) || (Motion == 1 && loop == 2)) loop = 3;
        return -1;
    }
    return 0;
}

// Prints dominoes on the board
void Game :: WriteDomino () {
list <Domino> :: iterator temp;
  cout << "\ n On the table: \ n";
for (temp = stol.begin (); temp! = stol.end (); temp ++) cout << "[" << temp-> A << "|" << temp-> B << "]"; cout << "\ n";
}

// Display the dominoes currently available to the player
void Game :: WriteUserBlocks (list <Domino> table _) {
list <Domino> :: iterator temp;
  cout << "\ n";
  for (temp = table_.begin (); temp! = table_.end (); temp ++) cout << "[" << temp-> A << "|" << temp-> B << "]" < <"";
cout << "\ n Your turn, Player" << Motion << "... \ n";
}

// Checks if the domino chosen by the player is in the pool of his blocks and whether they can be applied to the ends of X and Y.
list <Domino> Game :: MakeMove (char tab [], list <Domino> list_player) {
    int PlayerPosted = 0; // checks if the player actually printed the block
    list <Domino> :: iterator temp; list <Domino> :: iterator cousun;
    temp = list_player.begin ();

    for (; temp! = list_player.end (); temp ++) {// if we have it, and it is equal to the entered character, then
        if ((PlayerPosted == 0) && (((temp-> A == tab [0] - 48) && (temp-> B == tab [2] - 48)) || ((temp-> A = = tab [2] - 48) && (temp-> B == tab [0] - 48)))) {
            PlayerPosted = 1;
            temp = list_player.erase (temp); // take the player’s block
        }
    }
    if (PlayerPosted) {// match the block selected by the player to the end
        if (tab [0] - 48 == Y) {// add at the end: A B
            Domino block = Domino (Y, tab [2] - 48);
            stol.push_back (block); // add to the table
Y = tab [2] - 48;
        }
        else if (tab [2] - 48 == X) {// add at the beginning: A B
            Domino block = Domino (tab [0] - 48, X);
            stol.push_front (block); // add to the table
            X = tab [0] - 48;
        }
        else if ((tab [0] - 48 == X)) {// you need to change the block order // add at the beginning: B A
            Domino block = Domino (tab [2] - 48, X);
            stol.push_front (block); // add to the table
            X = tab [2] - 48;
        }
        else if (tab [2] - 48 == Y) {// add at the end: B A
            Domino block = Domino (Y, tab [0] - 48);
            stol.push_back (block); // add to the table
            Y = tab [0] - 48;
        }
        else {// laid out, but does not match any of the ends
cout << "\ n The selected domino does not match any of the tips! Select again. \ n";
fgets (tab, 50, stdin);
Game :: MakeMove (tab, list_player);
}
    }
    else {// block not printed
        cout << "\ n Inappropriate dominoes \ n"; //
        fgets (tab, 50, stdin);
        Game :: MakeMove (tab, list_player);
    }
  PlayerPosted = 0;
  return list_player;
}

// In case of a tie, the winner is selected based on the lesser amount of all his remaining dominoes
void Game :: CountPoints () {
    int suma1 = 0, suma2 = 0;
    list <Domino> :: iterator i;
    for (i = player1.begin (); i! = player1.end (); i ++) suma1 + = (i-> A + i-> B);
    for (i = player2.begin (); i! = player2.end (); i ++) suma2 + = (i-> A + i-> B);

if (suma1 <suma2)
    cout << "\ n Total points: \ n Player 1:" << suma2 << "\ n Player 2:" << suma1 << "\ n Victory for Player 1!";
else if (suma1> suma2)
    cout << "\ n Total points: \ n Player 1:" << suma2 << "\ n Player 2:" << suma1 << "\ n Victory for Player 2!";
else cout << "\ n Total points: \ n Player 1:" << suma1 << "\ n Player 2:" << suma2;
}

void Game :: Lookfromthetable (Domino domino) {
    list <Domino> :: iterator temp; temp = stol.begin ();
    for (; temp! = stol.end (); temp ++) {
        if ((((temp-> A == domino.A) && (temp-> B == domino.B)) || ((temp-> B == domino.A) && (temp-> A == domino .B)))
        temp = stol.erase (temp);
    }
}
