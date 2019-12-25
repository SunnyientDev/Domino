//Связывает всe из Domino.cpp
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <list>
#include "domino.h"
#include "handling.h"
using namespace std;

class Game : public Handling {
public:
    list<Domino> stol;
    list<Domino> player1;
    list<Domino> player2;
    list<Domino> nobody; // украден для частного

    int Motion;
    int X; // хранит начало вывода
    int Y; // хранит конец вывода
    int loop; // предотвращает петли, вызванные отсутствием доминошек у обоих игроков

    void WriteDomino(); // Пишем все доминошки на боарде
    void Lookfromthetable(Domino); // Возвращение на одно состояние назад
    int AddDomino(list<Domino>); // Добавляет штрафные доминошки из листа «без человека», когда у игрока нет подходящих доминошек
    void MakeDomino(); // Распределяет домино в начале новой игры
    int CheckMotion(list<Domino>); // Проверяет, может ли игрок сделать ход
    void WriteUserBlocks(list<Domino>); // Обновляет список блоков (доминошек) после добавления новой доминошки
    list<Domino> MakeMove(char[], list<Domino>); // Проверяет, может ли текущий игрок сделать ход
    void CountPoints(); // Определяет победителя в случае ничьей
};
#endif 