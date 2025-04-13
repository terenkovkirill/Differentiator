#include <stdlib.h>
#include <assert.h>
#include "ExpressionTree.h"

Node_t* CreateNode(int value, int type, Node_t* left, Node_t* right)
{
    Node_t* node = (Node_t *)calloc(1, sizeof(Node_t));

    node->value = value;
    node->type = type;
    node->left = left;
    node->right = right;

    return node;
}


CodeError GrafDump(Node_t* node)
{
    if (!node) return NULL_PTR;

    FILE* file = fopen("ExpressionTree.dot", "w");
    fprintf(file, "digraph\n{\n");

    RecursiveGrafDump(node, file);

    fprintf(file, "} \n");
    fclose(file);

    return OK;
}


Node_t* RecursiveGrafDump(Node_t* node, FILE* file)
{
    assert(node != NULL);

    fprintf(file, "     node%p[shape=\"Mrecord\", label=\"{node%p | value = %d | type = %d | {left = %p | right = %p}}\"] \n", node, node, node->value, node->type, node->left, node->right);

    if (node->left != NULL)
    {
        Node_t* left =  RecursiveGrafDump(node->left, file);
        fprintf(file, "     node%p -> node%p \n\n", node, left);
    }

    if (node->right != NULL)
    {
        Node_t* right =  RecursiveGrafDump(node->right, file);
        fprintf(file, "     node%p -> node%p \n\n", node, right);
    }

    return node;
}


CodeError Calculate(Node_t* node)
{
    //===========CheckNode=============================

    assert(node != NULL);

    if ((node->left != NULL) ^ (node->right != NULL))                       //Отсутствует один из двух потомков
        return INCORRECT_TREE;
    
    if (node->type == OP && node->left == NULL && node->right == NULL)
        return INCORRECT_TREE;

    if (node->type == NUM && node->left != NULL && node->right != NULL)
        return INCORRECT_TREE;

    //=================================================

    if (node->type == NUM)
        return OK;
    
    Calculate(node->left);
    Calculate(node->right);

    //if (node->type == OP && node->left->type == NUM && node->right->type == NUM)     --может пригодится при добавлении переменной

    node->type = NUM;

    switch(node->value)
    {
        case '+':
            node->value = node->left->value + node->right->value;
            break;
        
        case '-':
            node->value = node->left->value - node->right->value;
            break;
        
        case '*':
            node->value = node->left->value * node->right->value;
            break;
        
        case '/':
            node->value = node->left->value / node->right->value;
            break;
    }

    return OK;
}


CodeError GrafPicture(Node_t* node)
{
    if (!node) return NULL_PTR;

    FILE* file = fopen("TreePicture.dot", "w");
    fprintf(file, "digraph\n{\n");

    RecursiveGrafPicture(node, file);

    fprintf(file, "} \n");
    fclose(file);

    return OK;
}


Node_t* RecursiveGrafPicture(Node_t* node, FILE* file)
{
    assert(node != NULL);

    switch(node->type)
    {
        case NUM:
            fprintf(file, "     node%p[shape=\"circle\", width = 0.8, height = 0.8, label=\"%d\"] \n", node, node->value);
            break;

        case VAR:
            fprintf(file, "     node%p[shape=\"circle\", width = 0.8, height = 0.8, label=\"%c\"] \n", node, node->value);
            break;

        case OP:
            fprintf(file, "     node%p[shape=\"circle\", width = 0.8, height = 0.8, label=\"%c\"] \n", node, node->value);
            break;
        
        default:
            fprintf(stderr, "[INFO] %s:%d %s() Incorrect node->type value \n", __FILE__, __LINE__, __func__);
            break;
    }

    if (node->left != NULL)
    {
        Node_t* left =  RecursiveGrafPicture(node->left, file);
        fprintf(file, "     node%p -> node%p \n\n", node, left);
    }

    if (node->right != NULL)
    {
        Node_t* right =  RecursiveGrafPicture(node->right, file);
        fprintf(file, "     node%p -> node%p \n\n", node, right);
    }

    return node;
}