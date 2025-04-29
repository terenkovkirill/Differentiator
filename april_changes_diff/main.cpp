#include "diff.h"

int main()
{
    const struct VarValue var_value = {102, 0};
    
    Node_t* root1 = NULL;
    ReadExpression(&root1, "Expression.txt");
    
    CodeError error_code = CheckTree(root1);
    if (error_code != OK)
        fprintf(stderr, "[ERROR] %s:%d %s() Incorrect_tree: %d \n", __FILE__, __LINE__, __func__, error_code);

    GrafDump(root1);

    GrafPicture(root1);
    
    int result = Calculate(root1, var_value);
    if (result == INCORRECT_TREE || result == DIV_BY_ZERO)
        fprintf(stderr, "[ERROR] %s:%d %s() Error: %d in function Calculate() \n", __FILE__, __LINE__, __func__, result);

    printf("Expression value = %d \n", result);

    // Node_t* root2 = Diff(root1);
    // GrafPicture(root2);

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
10. Поработать с функцией CAlculate: 
    10.1 Добавить case FUNC 
    10.2 Сделать необязательной пердачу var_value
    10.3 Начать создавать копию дерева
    10.4 Сделать возможным одного потомка для OP
11. Добавить SIN, COS, POWER
//kl'gnbsbs'
*/

//Отключил -fsanitize=address

//(/(+(102)(3))(-(1000)(7)))



/*
Ограничения для Expression:
1. Показатель степени - const выражение
*/