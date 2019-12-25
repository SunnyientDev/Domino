#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
  #include <utility>
  #include "game.h"
  #include <time.h>
using namespace std;

// Создание изменяющихся списков для каждого игрока. Используется в основной функции только один раз при запуске новой игры.
void Game::MakeDomino(){
    int loc; //location
    int x = 0; 

    for(int i = 0; i <= 6; i++){
        for(int j = x; j <= 6; j++){
            loc = rand() % 3; //0,1,2!!
            
            switch (loc){
              case 0:{
                  if(player1.size() < 7){
                      Domino temp1 = Domino(i, j);
                      player1.push_back(temp1);}
                  else if(nobody.size() < 14){ // если бы не было, было бы слишком мало блоков
                      Domino temp3 = Domino(i, j);
                      nobody.push_back(temp3);}
                  break;
              }
              
              case 1:{
                  if(player2.size() < 7){
                      Domino temp2= Domino(i, j);
                      player2.push_back(temp2);}
                  else if(player1.size() < 7){ // если бы не было, было бы слишком мало блоков
                      Domino temp1= Domino(i, j);
                      player1.push_back(temp1);}
                  break;
              }
              
              case 2:{
                  if(nobody.size() < 14){
                      Domino temp3= Domino(i, j);
                      nobody.push_back(temp3);}
                  else if(player2.size() < 7){
                      Domino temp2= Domino(i, j);
                      player2.push_back(temp2);}
                  break;
              }
          }
        }
        x++;
    }

    x = rand() % 14;
     // Первый блок, брошенный в таблицу, является случайным
    list <Domino>::iterator iter; iter = nobody.begin();
    for(; x > 0; x--) iter++;
    Domino start = Domino(iter -> A, iter -> B);
    stol.push_back(start); // положить первое домино на стол
    X = iter -> A; Y = iter -> B;
    nobody.erase(iter); // удалить их из чьего-либо списка
}

// Добавляет штрафные доминошки из листа «нет владельца», когда у игрока нет подходящих доминошек
int Game::AddDomino(list <Domino> list_player){
    bool take = 0; // Определитель доминошки

    if(nobody.size() < 1){ // Если больше нет блоков
        cout << "\n Домино закончились на базаре. Игра окончена. \n";
        setPlay(false); // Заканчиваем игру :(
        return 0; }

    while((nobody.size() > 0) && (take == 0)){ // если на базаре есть фишки и он может сделать ход (Ведь может попасться фишка, которая не подходит)
        list <Domino>::iterator iter; iter = nobody.begin();
        Domino temp2 = Domino(iter -> A, iter -> B); //Можно написать просто как A, B. Просто так правильнее
        list_player.push_back(temp2); // отдаем домино игроку
        nobody.erase(iter); // Удаляем доминошку из списка nobody

        printf("Игрок %d получил: [%d|%d].\n", Motion, iter -> A, iter -> B);
        list <Domino>::iterator temp;

        for(temp = list_player.begin(); temp != list_player.end(); temp++)
            if ((temp-> A == X) || (temp-> B == X) || (temp->A == Y) || (temp->B == Y)) take = 1; // Если можем сделать ход!
       (Motion == 1)? (player1 = list_player) : (player2 = list_player); 
    }
    return 1;
}

 // Проверяет, может ли игрок сделать ход. Если нет, то вызывает функцию добавления доминошек
int Game::CheckMotion(list <Domino> list_player){
	list <Domino>::iterator temp;
	for(temp = list_player.begin(); temp != list_player.end(); temp++){ // Можем сделать ход
        if((temp-> A == X) || (temp->A == Y) || (temp->B == Y) || (temp->B == X)){ loop = 0; return 1; }
	}
  
  cout << "\n Игрок "<< Motion <<" не может сделать ход.\n";
  if(nobody.size() > 0){ AddDomino(list_player); return 1; }
    else{
        cout << "\n Нет свободных фишек для игрока. \n";
	      if(Motion == 1 && loop == 0) loop = 1;
        else if(Motion == 2 && loop == 0) loop = 2;
        else if((Motion == 2 && loop == 1) || (Motion == 1 && loop == 2)) loop = 3;
        return -1;
    }
    return 0;
}

//Печатает доминошки на борде
void Game::WriteDomino(){
	list <Domino>::iterator temp;
  cout << "\n На столе: \n";
	for(temp = stol.begin(); temp != stol.end(); temp++) cout << " [" << temp->A << "|" << temp->B <<"] "; cout << "\n";
}

// Выводим доминошки, доступные в данный момент игроку
void Game::WriteUserBlocks(list <Domino> table_){
	list <Domino>::iterator temp;
  cout << "\n";
  for(temp = table_.begin(); temp != table_.end(); temp++) cout << "["<< temp->A<<"|"<< temp->B<<"]" << "  ";
	cout << "\n Ваш ход, Игрок " << Motion << "... \n";
}

// Проверяет, находится ли домино, выбранное игроком, в пуле его блоков и можно ли их применить к концам X и Y.
list <Domino> Game::MakeMove(char tab[], list <Domino> list_player){
    int PlayerPosted = 0; // проверяет, действительно ли игрок напечатал блок
    list <Domino>::iterator temp; list <Domino>::iterator cousun;
    temp = list_player.begin();

    for(; temp != list_player.end(); temp++){ // если он у нас есть, и он равен введенному символу, то
        if((PlayerPosted == 0) && (((temp->A == tab[0] - 48) && (temp->B == tab[2] - 48)) || ((temp->A == tab[2] - 48) && (temp->B == tab[0] - 48)))){
            PlayerPosted = 1;
            temp = list_player.erase(temp); // взять блок у игрока
        }
    }
    if(PlayerPosted){ // сопоставить выбранный игроком блок с концом
        if(tab[0] - 48 == Y){ // добавить в конце: A B
            Domino block=Domino(Y, tab[2] - 48);
            stol.push_back(block); // добавить в таблицу
	          Y = tab[2] - 48;
        }
        else if(tab[2] - 48 == X){ // добавить в начале: A B
            Domino block = Domino(tab[0] - 48, X);
            stol.push_front(block); //добавить на стол
            X = tab[0] - 48;
        }
        else if((tab[0] - 48 == X)){ // вам нужно изменить порядок блока // добавить в начале: B A
            Domino block=Domino(tab[2] - 48, X);
            stol.push_front(block); //добавить на стол
            X = tab[2] - 48;
        }
        else if(tab[2] - 48 == Y){ // добавить в конце: B A
            Domino block=Domino(Y, tab[0] - 48);
            stol.push_back(block); //добавить на стол
            Y = tab[0] - 48;
        }
        else{ // выложил, но не соответствует ни одному из концов
		  cout << "\n Выбранное домино не соответствует ни одному из советов! Выберите снова. \n";
		  fgets(tab, 50, stdin);
		  Game::MakeMove(tab, list_player);
	    }
    }
    else{ // не напечатан блок
        cout << "\n Неуместные домино \n"; //
        fgets(tab, 50, stdin);
        Game::MakeMove(tab, list_player);
    }
  PlayerPosted = 0;
  return list_player;
}

// В случае ничьей победитель выбирается на основании меньшей суммы всех его оставшихся домино
void Game::CountPoints(){
    int suma1 = 0, suma2 = 0;
    list <Domino>::iterator i;
    for(i = player1.begin(); i != player1.end(); i++) suma1 += (i->A + i->B);
    for(i = player2.begin(); i != player2.end(); i++) suma2 += (i->A + i->B);

	if(suma1 < suma2) 
    cout << "\n Всего очков: \n Игрок 1:" << suma2 << "\n Игрок 2: "<< suma1 << "\n Победа для Игрока 1!";
	else if(suma1 > suma2) 
    cout << "\n Всего очков: \n Игрок 1:" << suma2 <<"\n Игрок 2: "<< suma1 << "\n Победа для Игрока 2!";
	else cout << "\n Сумма очков: \n Игрок 1:" << suma1 <<"\n Игрок 2: "<< suma2;
}

void Game::Lookfromthetable(Domino domino){
    list <Domino>::iterator temp; temp = stol.begin();
    for(; temp != stol.end(); temp++){
        if(((temp->A == domino.A) && (temp->B == domino.B)) || ((temp->B == domino.A) && (temp->A == domino.B)))
        temp = stol.erase(temp);
    }
}