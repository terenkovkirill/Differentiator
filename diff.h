#include <stdio.h>

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

Node_t* NewNode(Node_t* node, int type, int value);
Node_t* ReadExpression(const char* file);
Node_t* CreatTree(char *buffer);
//void PrintPreorder(Node_t* node, const char* file);
//int GrafDump(Node_t* node);
