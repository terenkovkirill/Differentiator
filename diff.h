#ifndef DIFF_H
#define DIFF_H


#include <stdio.h>

#include "RecursiveDescent.h"

struct Node_t
{
    int type;
    int value;
    Node_t* left;
    Node_t* right;
};

enum NodeType
{
    OP = 100,
    VAR = 101,
    NUM = 102
};

enum OperationType
{
    SUB = '-',
    ADD = '+',
    DIV = '/',
    MUL = '*'
};

Node_t* NewNode(int type, int value, Node_t* left, Node_t* right);
struct ArgRec ReadExpression(const char* file);
int GrafDump(Node_t* node);
int PreorderTraversal(Node_t* node, FILE* graf_dump);

//Node_t* CreatTree(char *buffer);



#endif 