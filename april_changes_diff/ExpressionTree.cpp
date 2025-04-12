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
