// nobody ... - the object does not belong to the players

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
  #include "game.h"
  #include <time.h>

using namespace std;

void print_welcome () {
  cout << "Welcome to dominoes! \ n";
  cout << "______________________________________________ \ n";
  cout << "The input format in the game: \ n";
  cout << "\ t 1. To go back one step, press Z \ n";
  cout << "\ t 2. Domino bones are entered this way: A.B \ n \ n";
}

int main () {
    print_welcome ();
    srand (time (NULL));

    Game game;
    game.Motion = 1; // determines which player is walking now
    //game.loops = 0;
    game.loop = 1; // if the player did something wrong, then the move still belongs to him

    Handling command; // Access to movements on the board / command - working variable
    command.setPlay (false); // Until we start the game

    char moth1 [6], moth2 [6]; // a total of six different elements / Movement

  string default_console = "\ 033 [0m";
  string color1 = "\ 033 [033m", color2 = "\ 033 [032m";

cout << "Let's start the game? [Y / N] \ n";

  char setting; // check letters
while (command.getPlay () == 0) {
fgets (& setting, 50, stdin);

    if ((setting == 89) || (setting == 121)) {// Y
      game.MakeDomino ();
      command.setPlay (true);
      }
else if ((setting == 78) || (setting == 110)) return 0; // N
else cout << "Retry the command, please \ n";
}

while (command.getPlay ()) {
system ("clear");

      switch (game.Motion) {
        case 1:
            game.WriteDomino ();
            
            if (game.CheckMotion (game.player1) == 1) {
cout << color1;
              game.WriteUserBlocks (game.player1);
              fgets (moth1, 50, stdin);
if ((moth1 [0] == 90) || (moth1 [0] == 122)) {// if 'z', I will return to the situation from the moment back

          if (game.stol.size ()> 1) {
Domino block = Domino (0, 0);
block = command.getTop ();
list <Domino> fresh;
fresh = command.UndoMove (game.player2);
game.player2 = fresh;
game.Lookfromthetable (block); // take from the table
game.Motion = 2; // gives the previous player his move
}
else {
cout << "We are back to the beginning of the game!";
}
}
else {
game.player1 = game.MakeMove (moth1, game.player1);
command.SaveMove (moth1 [0] - 48, moth1 [2] - 48);} // save the move to history
cout << default_console << "\ n";
}

if (game.loop <3) game.Motion = 2;
else {game.Motion = 0; command.setPlay (false);}
break;

case 2:
            game.WriteDomino ();
if (game.CheckMotion (game.player2) == 1) {
cout << color2;
game.WriteUserBlocks (game.player2);
fgets (moth2, 50, stdin);
                if ((moth2 [0] == 90) || (moth2 [0] == 122)) {// if 'z', go back
if (game.stol.size ()> 1) {
Domino block = Domino (0, 0);
block = command.getTop ();
list <Domino> fresh;
fresh = command.UndoMove (game.player1);
game.player1 = fresh;
game.Lookfromthetable (block); // take from the table
game.Motion = 1; // gives the previous player his move
}
else {
cout << "We are back to the beginning of the game!";

}

}
                else {
                    game.player2 = game.MakeMove (moth2, game.player2);
                    command.SaveMove (moth2 [0] - 48, moth2 [2] - 48);
                } // save the move to history
                cout << default_console << "\ n";
            }
            if (game.loop <3) game.Motion = 1;
            else {game.Motion = 0; command.setPlay (false);}
            break;
}
        if (game.player1.size () == 0 || game.player2.size () == 0) command.setPlay (false); // if any player got rid of all the dominoes, stop the game
}
game.CountPoints ();

return 0;
}
