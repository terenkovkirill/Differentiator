#include <stdio.h>

struct ArgRecursion
{
    int p;
    const char *s;
};

enum Errors_of_recursion
{
    DOES_NOT_PROCESS_ELEMENTS = 1001,
    NO_CLOSING_PARANTHESIS = 1002
};

#define SYNTAX_ERROR(error) SyntaxError(error, __func__, __LINE__)

int GetG(ArgRecursion* arg_rec);
int GetN(ArgRecursion* arg_rec);
int GetE(ArgRecursion* arg_rec);
int GetP(ArgRecursion* arg_rec);
int GetT(ArgRecursion* arg_rec);
int SyntaxError(int error, const char* func, int line);