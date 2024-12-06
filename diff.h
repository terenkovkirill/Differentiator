#ifndef DIFF_H
#define DIFF_H


#include <stdio.h>


#define _NUM(arg) NewNode(NUM, arg, NULL)
#define _X NewNode(VAR, 1,NULL, NULL)

#define _ADD(node1, node2) NewNode(OP, ADD, node1, node2)
#define _SUB(node1, node2) NewNode(OP, SUB, node1, node2)
#define _DIV(node1, node2) NewNode(OP, DIV, node1, node2)
#define _MUL(node1, node2) NewNode(OP, MUL, node1, node2)

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
int GrafDump(Node_t* node);
int PreorderTraversal(Node_t* node, FILE* graf_dump);
Node_t* diff(Node_t* node);

//Node_t* CreatTree(char *buffer);



#endif 