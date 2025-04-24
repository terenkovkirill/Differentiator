#ifndef DIFF_H
#define DIFF_H

#include "ExpressionTree.h"

#define dL Diff(node->left) 
#define cL CopyTree(node->left)
#define dR Diff(node->right)
#define cR CopyTree(node->right)

#define _ADD  (left, right) CreateNode(ADD,   OP, left, right)
#define _SUB  (left, right) CreateNode(SUB,   OP, left, right)
#define _MUL  (left, right) CreateNode(MUL,   OP, left, right)
#define _DIV  (left, right) CreateNode(DIV,   OP, left, right)


Node_t* CopyTree(Node_t* node);
Node_t* Diff(Node_t* node);

#define _POWER(left, right) CreateNode(POWER, OP, left, right)
#endif