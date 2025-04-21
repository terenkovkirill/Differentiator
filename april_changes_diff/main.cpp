#include "ExpressionTree.h"

int main()
{
    const struct VarValue var_value = {102, 0};

    // Node_t* num1000 = CreateNode(10,   NUM, NULL,    NULL);
    // Node_t* num7    = CreateNode(1,    NUM, NULL,    NULL);
    // Node_t* num102   = CreateNode(102, NUM, NULL,    NULL);
    // Node_t* num3    = CreateNode(24,   NUM, NULL,    NULL);
    // Node_t* add     = CreateNode('+',  OP,  num102,   num3);
    // Node_t* sub     = CreateNode('-',  OP,  num1000, num7);
    // Node_t* div     = CreateNode('/',  OP,  add,     sub );

    Node_t* div = NULL;
    ReadExpression(&div, "Expression.txt");

    GrafDump(div);

    GrafPicture(div);
    
    Calculate(div, var_value);
    printf("Expression value = %d \n", div->value);

    //GrafPicture(div);

    return 0;
}

/*
TODO:
0. Объединения или Union
1. Функция печати в файл в формате TEX
2. Написать функцию считывания в формате PREORDER                                           +
3. Начать работать с GDB
4. Позаботиться о считывании всякой фигни из Expression.txt (x (вместо X), одно число, ...)
5. Добавить Diff() + #define-ы
*/

//Отключил -fsanitize=address

//(/(+(102)(3))(-(1000)(7)))