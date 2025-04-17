#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ExpressionTree.h"

Node_t* CreateNode(int value, int type, Node_t* left, Node_t* right)
{
    Node_t* node = (Node_t *)calloc(1, sizeof(Node_t));

    node->value = value;
    node->type  = type;
    node->left  = left;
    node->right = right;

    return node;
}


CodeError CreateTree(Node_t* node, const char* file_name)
{
    FILE* file = fopen(file_name, "r");

    if (file == NULL)
        fprintf(stderr, "[ERROR] %s:%d %s() NULL file pointer \n", __FILE__, __LINE__, __func__);
        return NULL_FILE_PTR;

    char* buffer = NULL;
    size_t buffer_len = 0;
    ssize_t file_len;

    file_len = getline(&buffer, &buffer_len, file);
    if (file_len == -1)
        fprintf(stderr, "[ERROR] %s:%d %s() File reading error \n", __FILE__, __LINE__, __func__);
        return READ_ERROR;
    
    //================TODO:========
    
    node = ReadChar(node, buffer);

    //=============================
    
    free(buffer);
    fclose(file);

    return OK;
}


Node_t* ReadChar(Node_t* node, char* buffer)
{
    int value = 0, value1 = 0;
    sscanf(buffer, "%d", value);            //считали (

    
    sscanf(buffer, "%d", value);

    switch(value)
    {
        case ADD:
            sscanf(buffer, "%d", value);                    // считываем )
            node->left  = ReadChar(node->left, buffer);
            node->right = ReadChar(node->right, buffer);
            return CreateNode(ADD, OP, node->left, node->right);

        case SUB:
            sscanf(buffer, "%d", value);                    // считываем )
            node->left  = ReadChar(node->left, buffer);
            node->right = ReadChar(node->right, buffer);
            return CreateNode(SUB, OP, node->left, node->right);

        case MUL:
            sscanf(buffer, "%d", value);                    // считываем )
            node->left  = ReadChar(node->left, buffer);
            node->right = ReadChar(node->right, buffer);
            return CreateNode(MUL, OP, node->left, node->right);

        case DIV:
            sscanf(buffer, "%d", value);                    // считываем )
            node->left  = ReadChar(node->left, buffer);
            node->right = ReadChar(node->right, buffer);
            return CreateNode(DIV, OP, node->left, node->right);
        
        case X:
            sscanf(buffer, "%d", value);                    // считываем )
            return CreateNode(X, VAR, NULL, NULL);
        
        case Y:
            sscanf(buffer, "%d", value);                    // считываем )
            return CreateNode(Y, VAR, NULL, NULL);
        
        default:
            sscanf(buffer, "%d", value1);                    // считываем )
            return CreateNode(value, VAR, NULL, NULL);

    }
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
    
    switch(node->type)
    {
        case NUM:
            fprintf(file, "     node%p[shape=\"Mrecord\", style=\"filled\", fillcolor=\"#9ACD32\", label=\"{node%p | value = %d | type = %d | {left = %p | right = %p}}\"] \n", node, node, node->value, node->type, node->left, node->right);
            break;

        case VAR:
            fprintf(file, "     node%p[shape=\"Mrecord\", style=\"filled\", fillcolor=\"#FFA07A\", label=\"{node%p | value = %d | type = %d | {left = %p | right = %p}}\"] \n", node, node, node->value, node->type, node->left, node->right);
            break;
        
        case OP:
            fprintf(file, "     node%p[shape=\"Mrecord\", style=\"filled\", fillcolor=\"#87CEEB\", label=\"{node%p | value = %d | type = %d | {left = %p | right = %p}}\"] \n", node, node, node->value, node->type, node->left, node->right);
            break;
        
        default:
            fprintf(stderr, "[ERROR] %s:%d %s() Incorrect node->type \n", __FILE__, __LINE__, __func__);
            break;
    }

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


CodeError CheckNode(Node_t* node)
{
    assert(node != NULL);

    if ((node->left != NULL) ^ (node->right != NULL))                       //Отсутствует один из двух потомков
        return ONLY_ONE_CHILD;
    
    if (node->type == OP && node->left == NULL && node->right == NULL)
        return OP_IS_A_LEAF;

    if (node->type == NUM && node->left != NULL && node->right != NULL)
        return NUM_IS_NOT_LEAF;

    return OK;
}


int Calculate(Node_t* node, struct VarValue var_value)
{
    CodeError return_value = CheckNode(node);
    if (return_value != OK)
    {
        fprintf(stderr, "[ERROR] %s:%d %s() Incorrect_tree: %d \n", __FILE__, __LINE__, __func__, return_value);
        return INCORRECT_TREE;
    }

    if (node->type == NUM)
        return OK;
    
    if (node->type == VAR)
    {
        switch(node->value)
        {
            case X:
                node->value = var_value.x;
                break;

            case Y:
                node->value = var_value.y;
                break;

            default:
                fprintf(stderr, "[ERROR] %s:%d %s() Incorrect node->value for node->type = VAR \n", __FILE__, __LINE__, __func__);
                break;
        }

        node->type = NUM;
        
        return OK;
    }
    
    Calculate(node->left,  var_value);
    Calculate(node->right, var_value);

    CodeError error_code = ComputeNode(&node);
    if (error_code == OK)
        return OK;
    else
    {
        fprintf(stderr, "[ERROR] %s:%d %s() Tre error code of the ComputeNode() function = %d \n", __FILE__, __LINE__, __func__, error_code);
        return CALCULATE_ERROR;
    }
}


CodeError ComputeNode(Node_t** node)
{
    if (node == NULL  || *node == NULL)
        return NULL_PTR;

    switch((*node)->value)
    {
        case ADD:
            (*node)->value = (*node)->left->value + (*node)->right->value;
            break;
        
        case SUB:
            (*node)->value = (*node)->left->value - (*node)->right->value;
            break;
        
        case MUL:
            (*node)->value = (*node)->left->value * (*node)->right->value;
            break;
        
        case DIV:
            (*node)->value = (*node)->left->value / (*node)->right->value;
            break;
        
        default:
            fprintf(stderr, "[ERROR] %s:%d %s() Incorrect node->value for node->type = OP \n", __FILE__, __LINE__, __func__);
            return INCORRECT_TREE;
    }

    (*node)->type = NUM;

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
            fprintf(file, "     node%p[shape=\"circle\", style=\"filled\", fillcolor=\"#9ACD32\",  width = 0.8, height = 0.8, label=\"%d\"] \n", node, node->value);
            break;

        case VAR:
            if (node->value == X)
                fprintf(file, "     node%p[shape=\"circle\", style=\"filled\", fillcolor=\"#FFA07A\", width = 0.8, height = 0.8, label=\"%c\"] \n", node, node->value);

            else if (node->value== Y)
                fprintf(file, "     node%p[shape=\"circle\", style=\"filled\", fillcolor=\"#FFA07A\", width = 0.8, height = 0.8, label=\"%c\"] \n", node, node->value);

            break;

        case OP:
            fprintf(file, "     node%p[shape=\"circle\", style=\"filled\", fillcolor=\"#87CEEB\", width = 0.8, height = 0.8, label=\"%c\"] \n", node, node->value);
            break;
        
        default:
            fprintf(stderr, "[ERROR] %s:%d %s() Incorrect node->type value \n", __FILE__, __LINE__, __func__);
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