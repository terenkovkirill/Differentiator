#include "ExpressionTree.h"

int main()
{
    Node_t* num1000 = CreateNode(1000, NUM, NULL,    NULL);
    Node_t* num7    = CreateNode(7,    NUM, NULL,    NULL);
    Node_t* num10   = CreateNode(10,   NUM, NULL,    NULL);
    Node_t* num3    = CreateNode(3,    NUM, NULL,    NULL);
    Node_t* add     = CreateNode(1,    OP,  num10,   num3);
    Node_t* sub     = CreateNode(2,    OP,  num1000, num7);
    Node_t* div     = CreateNode(4,    OP,  add,     sub );

    GrafDump(div);
    
    return 0;
}

/*
TODO:
1. Сделать цветные узлы в GrafDump
2. Сделать функцию расчёта выражений (можно добавить глобальную переменную со значением x в данный момент)
3. Объединения или Union
4. Функция печати в файл в формате TEX
5. Сделать GrafDump с неразделёнными ячейками (только значение или операция)
*/

//Отключил -fsanitize=address