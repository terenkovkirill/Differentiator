#include "diff.h"

int main()
{
    //const struct VarValue var_value = {102, 0};

    Node_t* root1 = NULL;
    ReadExpression(&root1, "Expression.txt");

    GrafDump(root1);

    // GrafPicture(root1);
    
    // Calculate(root1, var_value);
    // printf("Expression value = %d \n", root1->value);

    Node_t* root2 = Diff(root1);
    GrafPicture(root2);

    return 0;
}

/*
TODO:
0. Объединения или Union
1. Функция печати в файл в формате TEX
2. Спросить у Макса про assert(0) && TEXT_DUMP
3. Начать работать с GDB
4. Позаботиться о считывании всякой фигни из Expression.txt (x (вместо X), одно число, ...)
5. Добавить Diff() + #define-ы                                                                  +
6. Поделить всё на файлы                                                                        +
7. Добавить возможность считывания sin                                                 
7. Узнать про зависимости файлов.cpp от файлов.h в Makefile
*/

//Отключил -fsanitize=address

//(/(+(102)(3))(-(1000)(7)))