//nobody... - объект не принадлежит игрокам

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
  #include "game.h"
  #include <time.h>

using namespace std;

void print_welcome(){
  cout << "Добро пожаловать в домино! \n";
  cout << "______________________________________________\n";
  cout << "Формат ввода в игре: \n";
  cout << "\t 1.Чтобы вернуться на шаг назад - нажмите Z \n";
  cout << "\t 2.Кости домино вводятся таким образом: A.B \n \n";
}

int main(){
    print_welcome();
    srand(time(NULL));

    Game game;
    game.Motion = 1; //определяет, какой игрок ходит сейчас
    //game.loops = 0;
    game.loop = 1; // если игрок сделал что-то не так, то ход по-прежнему принадлежит ему

    Handling command; //Обращение к перемещениям на борде/ command - рабочая переменная
    command.setPlay(false); // Пока не начинаем игру

    char moth1[6], moth2[6]; //всего шесть различных элементов/ Движение

  string default_console = "\033[0m";
  string color1 = "\033[033m", color2 = "\033[032m";

	cout << "Начнём игру? [Y/N] \n";

  char setting ; // проверка букв 
	while(command.getPlay() == 0){
		fgets(&setting , 50, stdin);
		
    if((setting == 89) || (setting == 121)){ //Y
      game.MakeDomino(); 
      command.setPlay(true);
      }
		else if((setting == 78) || (setting == 110)) return 0; //N
		else cout << "Повторите команду, пожалуйста \n";
	}

	while(command.getPlay()){
		system("clear");
	    
      switch(game.Motion){
        case 1: 
            game.WriteDomino();
            
            if (game.CheckMotion(game.player1) == 1){
				      cout << color1;
              game.WriteUserBlocks(game.player1);
              fgets(moth1, 50, stdin);
				      if((moth1[0] == 90) || (moth1[0] == 122)){ // если 'z', я вернусь к ситуации с момента назад
					
          if(game.stol.size() > 1){
					Domino block = Domino(0, 0);
					block = command.getTop();
					list <Domino> fresh;
					fresh = command.UndoMove(game.player2);
					game.player2 = fresh;
					game.Lookfromthetable(block); // взять из таблицы
					game.Motion = 2; // дает предыдущему игроку его ход
					}
					else{
					  cout << "Мы вернулись к началу игры!";
					}
				}
				else{
					game.player1 = game.MakeMove(moth1, game.player1);
					command.SaveMove(moth1[0] - 48, moth1[2] - 48);} // сохранить ход в историю
					cout << default_console << "\n";
			}

			if(game.loop < 3) game.Motion = 2;
			else {game.Motion = 0; command.setPlay(false);}
			break;

		case 2:
            game.WriteDomino();
		    if(game.CheckMotion(game.player2) == 1){
			  cout<<color2;
		        game.WriteUserBlocks(game.player2);
		        fgets(moth2, 50, stdin);
                if((moth2[0] == 90) || (moth2[0] == 122)){ // если 'z', вернемся назад
			      if(game.stol.size() > 1){
			      Domino block = Domino(0, 0);
			      block = command.getTop();
			      list <Domino> fresh;
			      fresh = command.UndoMove(game.player1);
			      game.player1 = fresh;
			      game.Lookfromthetable(block); // взять из таблицы
			      game.Motion = 1; // дает предыдущему игроку его ход
			      }
			      else{
				    cout << "Мы вернулись к началу игры!";
				    
				  }
			      
			    }
                else{
                    game.player2=game.MakeMove(moth2, game.player2);
                    command.SaveMove(moth2[0] - 48, moth2[2] - 48);
                } // сохранить ход в историю
                cout << default_console << "\n";
            }
            if(game.loop < 3) game.Motion = 1;
            else {game.Motion = 0; command.setPlay(false);}
            break;
	    }
        if(game.player1.size() == 0 || game.player2.size() == 0) command.setPlay(false); // если какой-либо игрок избавился от всех домино, прекращаем игру
	}
	game.CountPoints();

	return 0;
}
