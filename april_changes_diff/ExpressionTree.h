#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <stdio.h>
#define DEBUG

#ifdef DEBUG
    #define DBG(fmt, ...) \
        fprintf(stderr, "[DEBUG] %s:%d %s() " fmt "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
    #define DBG(fmt, ...)
#endif

struct Node_t
{
    int value;
    int type;
    Node_t* left;
    Node_t* right;
};

enum CodeError
{
    NULL_PTR        = 0,
    OK              = 1,
    INCORRECT_TREE  = 2,
    ONLY_ONE_CHILD  = 3,
    OP_IS_A_LEAF    = 4,
    NUM_IS_NOT_LEAF = 5,
    CALCULATE_ERROR = 6,
    NULL_FILE_PTR   = 7,
    READ_ERROR      = 8
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

struct VarValue
{
    int x;
    int y;
};

Node_t* CreateNode(int value, int type, Node_t* left, Node_t* right);
CodeError CreateTree(Node_t** node, const char* file);
Node_t* ReadChar(Node_t* node, char* buffer, int* ptr);
CodeError GrafDump(Node_t* node);
Node_t* RecursiveGrafDump(Node_t* node, FILE* file);
CodeError GrafPicture(Node_t* node);
Node_t* RecursiveGrafPicture(Node_t* node, FILE* file);
CodeError ComputeNode(Node_t** node);
int Calculate(Node_t* node, struct VarValue var_value);

#endif