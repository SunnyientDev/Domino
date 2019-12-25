#include <stdio.h>
#include <stdlib.h>
#include <iostream>
  #include "domino.h"
  #include <time.h>
using namespace std;

// Domino class, which is determined by the parameters A and B
Domino :: Domino (int A, int B) { // :: - an operator that is used to clarify (qualify) names. Domino is in the Domino namespace!
    this -> A = A;
    this -> B = B;
}
