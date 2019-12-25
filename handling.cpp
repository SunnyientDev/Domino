#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
   #include <utility>
   #include "handling.h"
   #include "game.h"
using namespace std;

bool Handling :: getPlay () {return play; }
void Handling :: setPlay (bool stan) {play = stan;}
Domino Handling :: getTop () {return setup.top (); }

void Handling :: SaveMove (int a, int b) {
   Domino block = Domino (a, b); setup.push (block); }
  

list <Domino> Handling :: UndoMove (list <Domino> lista) {
   cout << "The recall procedure. \ n";
   Domino block = Domino (0,0);
   block.A = setup.top (). A; // save the value of the block
   block.B = setup.top (). B;
   setup.pop (); // delete
   lista.push_back (block); // gives the previous player his domino
   return lista;
}
