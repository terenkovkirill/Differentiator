#include <assert.h>
#include "diff.h"


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
        switch(node->value)
        {
            case ADD:
                return _ADD(dL, dR);

            case SUB:
                return _SUB(dL, dR);

            case MUL:
                return _ADD(_MUL(dL, cR), _MUL(cL, dR));

            case DIV:
                return _DIV(_SUB(_MUL(dL, cR), _MUL(dR, cL)), _MUL(cR, cR));
            
            // case POWER:                     //только для const показателя
            //     число = Calculate(node->right, var_value);      //Сделать необязательной пердачу var_value && начать создавать копию дерева
            //     Node_t* power1 = CreateNode(число, NUM, NULL, NULL);
            //     Node_t* power2 = CreateNode(число - 1, NUM, NULL, NULL);
            //     return _MUL(power1, _POWER(cR, power2));

            default:
                fprintf(stderr, "[ERROR] %s:%d %s() Incorrect node->value for node->type = OP \n", __FILE__, __LINE__, __func__);
                return NULL;
        }
    }

    else if (node->type == FUNC)
    {
        switch(node->value)
        {
            case SIN:
                return CreateNode(COS, FUNC, NULL, CopyTree(node->left));
            
            case COS:
                return CreateNode(SUB, OP, NULL, CreateNode(COS, FUNC, NULL, CopyTree(node->left))); 

            default:
                fprintf(stderr, "[ERROR] %s:%d %s() Incorrect node->value for node->type = FUNC \n", __FILE__, __LINE__, __func__);
                return NULL;
        }
    }

    else 
    {
        fprintf(stderr, "[ERROR] %s:%d %s() Incorrect node->type \n", __FILE__, __LINE__, __func__);
        return NULL;
    }
}