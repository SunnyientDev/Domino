#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED
#include <list>
#include <stack>
#include "domino.h"
using namespace std;

class Handling{ //Обращение
private:
     bool play;
     stack <Domino> setup;

public:
    void SaveMove(int a, int b);
    list <Domino> UndoMove(list<Domino>);
    bool getPlay();
    void setPlay(bool);
    Domino getTop();
};
#endif 