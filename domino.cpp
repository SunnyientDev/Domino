#include <stdio.h>
#include <stdlib.h>
#include <iostream>
  #include "domino.h"
  #include <time.h>
using namespace std;

//Класс доминошка, которая определяется параметрами A и B
Domino::Domino(int A, int B){ // :: - оператор, который используется для уточнения (квалификации) имен. Domino находится в пространстве имен Domino!
    this -> A = A;
    this -> B = B;
}

  /* Возьмём, к примеру, следующую строчку:
  another.setNumber(4);

  Во время компиляции строчка another.setNumber(4); конвертируется компилятором в следующее:

  setNumber(&another, 4); // объект another конвертировался из объекта, который находился перед точкой, в аргумент функции!

  Теперь это всего лишь стандартный вызов функции, а объект another (который ранее был отдельным объектом и находился перед точкой) теперь передаётся по адресу в качестве аргумента функции.

  Указатель *this — это скрытый константный указатель, что содержит адрес объекта, который вызывает метод класса.

  К любым переменным-членам внутри setNumber() добавляется префикс this->. Поэтому, когда мы говорим m_number = number, компилятор фактически выполняет this->m_number = number, который, в этом случае, обновляет another.m_number на number. */