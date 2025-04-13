#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <stdio.h>

struct Node_t
{
    int value;
    int type;
    Node_t* left;
    Node_t* right;
};

enum CodeError
{
    NULL_PTR = 0,
    OK       = 1,
    INCORRECT_TREE = 2
};

enum TypeNode
{
    NUM = 1,
    OP  = 2,
    VAR = 3
};

enum TypeOperation
{
    ADD = '+',
    SUB = '-',
    MUL = '*',
    DIV = '/'
};

enum NumVariable
{
    X = 'X',
    Y = 'Y'
};


Node_t* CreateNode(int value, int type, Node_t* left, Node_t* right);
CodeError GrafDump(Node_t* node);
Node_t* RecursiveGrafDump(Node_t* node, FILE* file);
CodeError GrafPicture(Node_t* node);
Node_t* RecursiveGrafPicture(Node_t* node, FILE* file);
CodeError Calculate(Node_t* node);

#endif