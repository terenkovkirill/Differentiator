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


#define TEXT_DUMP(dump_file, value, ptr, node, left, right, buffer) TextDump(dump_file, value, ptr, node, left, right, buffer, __FILE__, __LINE__, __func__)

struct Node_t
{
    int value;
    int type;
    Node_t* left;
    Node_t* right;
};

enum CodeError
{
    NULL_PTR                = 0,
    OK                      = 1,
    INCORRECT_TREE          = 2,
    FUNC_HAS_TWO_CHILDRENS  = 3,
    FUNC_IS_A_LEAF          = 4,
    OP_IS_A_LEAF            = 5,
    NUM_IS_NOT_LEAF         = 6,    
    CALCULATE_ERROR         = 7,
    NULL_FILE_PTR           = 8,
    READ_ERROR              = 9,
    DIV_BY_ZERO             = 10
};

enum TypeNode
{
    NUM = 1,
    OP  = 2,
    VAR = 3,
    FUNC = 4
};

enum TypeOperation
{
    ADD = '+',
    SUB = '-',
    MUL = '*',
    DIV = '/',
    POWER = '^'
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

enum ElementaryFunctions
{
    SIN = 's',
    COS = 'c',
    TAN = 't',
    EXP = 'e',
    LN  = 'l'   
};

const int LENGTH_LINE = 30;

Node_t* CreateNode(int value, int type, Node_t* left, Node_t* right);
CodeError ReadExpression(Node_t** node, const char* file);
Node_t* CreateTree(Node_t* node, char* buffer, int* ptr, int file_len, FILE* dump_file);
CodeError GrafDump(Node_t* node);
Node_t* RecursiveGrafDump(Node_t* node, FILE* file);
CodeError GrafPicture(Node_t* node);
Node_t* RecursiveGrafPicture(Node_t* node, FILE* file);
int Calculate(Node_t* node, struct VarValue var_value);
int ComputeNode(Node_t* node, int left, int right);
CodeError CheckTree(Node_t* node);
CodeError CheckNode(Node_t* node);
CodeError TextDump(FILE* dump_file, char value, int* ptr, Node_t* node, Node_t* left, Node_t* right, char* buffer, const char* file, int line, const char* func);


#endif