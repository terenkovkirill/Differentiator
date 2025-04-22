#include <assert.h>
#include "ExpressionTree.h"

Node_t* CopyTree(Node_t* node)
{
    assert(node != NULL);

    Node_t* temp_node = CreateNode(node->value, node->type, NULL, NULL);

    if (node->left)
        temp_node->left = CopyTree(node->left);

    if (node->right)
        temp_node->right = CopyTree(node->right);

    return temp_node;
}


Node_t* Diff(Node_t* node)
{
    assert(node != NULL);

    if (node->type == NUM)
        return CreateNode(0, NUM, NULL, NULL);

    else if (node->type == VAR)
        return CreateNode(1, NUM, NULL, NULL);
    
    else if (node->type == OP)
    {
        Node_t* temp_node = NULL;

        switch(node->value)
        {
            case ADD:
                return CreateNode(ADD, OP, Diff (node->left), Diff (node->right));

            case SUB:
                return CreateNode(SUB, OP, Diff (node->left), Diff (node->right));

            case MUL:
                temp_node = CreateNode(ADD, OP, NULL, NULL);
                temp_node->left = CreateNode(MUL, OP, Diff(node->left), CopyTree(node->right));
                temp_node->right = CreateNode(MUL, OP, CopyTree(node->left), Diff(node->right));

                return temp_node;
            
            default:
                fprintf(stderr, "[ERROR] %s:%d %s() Incorrect node->value for node->type = OP \n", __FILE__, __LINE__, __func__);
                return NULL;
        }
    }

    else 
    {
        fprintf(stderr, "[ERROR] %s:%d %s() Incorrect node->type \n", __FILE__, __LINE__, __func__);
        return NULL;
    }
}