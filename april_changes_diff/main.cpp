#include "ExpressionTree.h"

int main()
{
    const struct VarValue var_value = {102, 0};

    Node_t* num1000 = CreateNode(10, NUM, NULL,    NULL);
    Node_t* num7    = CreateNode(1,    NUM, NULL,    NULL);
    Node_t* num10   = CreateNode(X,    VAR, NULL,    NULL);
    Node_t* num3    = CreateNode(24,   NUM, NULL,    NULL);
    Node_t* add     = CreateNode('+',  OP,  num10,   num3);
    Node_t* sub     = CreateNode('-',  OP,  num1000, num7);
    Node_t* div     = CreateNode('/',  OP,  add,     sub );

    GrafDump(div);

    //GrafPicture(div);
    
    Calculate(div, var_value);
    printf("Expression value = %d \n", div->value);

    GrafPicture(div);

    return 0;
}

/*
TODO:
0. Избавиться от switch в RecursiveGrafPicture                                  +
1. Сделать цветные узлы в GrafDump
2. Сделать функцию расчёта выражений                                            +
2.1 Убрать CheckTree в отдельную функцию                                        +
2.5 Добавить переменную в Calculate                                             +
     (можно добавить структуру со значением x, y в данный момент)               +
2.9 Спросиль у Макса не нужно ли убрать switch-чи в отдельные функции
3. Объединения или Union
4. Функция печати в файл в формате TEX
5. Игрушечный GrafDump                                                          +
*/

//Отключил -fsanitize=address