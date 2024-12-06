#ifndef RECURSIVE_DESCENT_H
#define RECURSIVE_DESCENT_H


#include <stdio.h>

#include "diff.h"

struct ArgRec
{
    int p;
    char *s;
};

enum Errors_of_recursion
{
    DOES_NOT_PROCESS_ELEMENTS = 1001,
    NO_CLOSING_PARANTHESIS = 1002
};

#define SYNTAX_ERROR(error) SyntaxError(error, __func__, __LINE__)

Node_t* GetG(ArgRec* arg_rec);
Node_t* GetN(ArgRec* arg_rec);
Node_t* GetE(ArgRec* arg_rec);
Node_t* GetP(ArgRec* arg_rec);
Node_t* GetT(ArgRec* arg_rec);
int SyntaxError(int error, const char* func, int line);

struct ArgRec ReadExpression(const char* file);

#endif