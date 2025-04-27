#include "diff.h"

int main()
{
    //const struct VarValue var_value = {102, 0};
    
    Node_t* root1 = NULL;
    ReadExpression(&root1, "Expression.txt");
    
    CodeError error_code = CheckTree(root1);
    if (error_code != OK)
        fprintf(stderr, "[ERROR] %s:%d %s() Incorrect_tree: %d \n", __FILE__, __LINE__, __func__, error_code);

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
3. Начать работать с GDB
4. Позаботиться о считывании всякой фигни из Expression.txt (x (вместо X), одно число, ...)
7. Добавить возможность считывания sin                                                 
8. Узнать про зависимости файлов.cpp от файлов.h в Makefile
12. Dump CheckTree() в Log.txt && assert(0) - спросить у Макса
===========================
10. Поработать с функцией CAlculate Сделать необязательной пердачу var_value &&
                     начать создавать копию дерева && сделать возможным одного потомка для OP
11. Добавить SIN, COS, POWER

*/

//Отключил -fsanitize=address

//(/(+(102)(3))(-(1000)(7)))



/*
Ограничения для Expression:
1. Показатель степени - const выражение
*/