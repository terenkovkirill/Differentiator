#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
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


CodeError ReadExpression(Node_t** node, const char* file_name)
{
    assert(node != NULL);

    FILE* file = fopen(file_name, "r");
    if (file == NULL)
    {
        fprintf(stderr, "[ERROR] %s:%d %s() NULL file pointer \n", __FILE__, __LINE__, __func__);
        return NULL_FILE_PTR;
    }

    char* buffer = NULL;
    size_t buffer_len = 0;
    ssize_t file_len  = 0;  

    file_len = getline(&buffer, &buffer_len, file);
    if (file_len == -1)
    {
        fprintf(stderr, "[ERROR] %s:%d %s() File reading error \n", __FILE__, __LINE__, __func__);
        return READ_ERROR;
    }
    
    FILE* dump_file = fopen("Log.txt", "w");
    int ptr = 0;

    *node = CreateTree(*node, buffer, &ptr, file_len, dump_file);
    
    free(buffer);
    fclose(file);

    return OK;
}


Node_t* CreateTree(Node_t* node, char* buffer, int* ptr, int file_len, FILE* dump_file)
{
    assert(0 <= *ptr && *ptr < file_len - 1);
    Node_t* temp_node = NULL;

    if (buffer[*ptr] == '(')
    {
        (*ptr)++;                                                           //открываем (
        node = CreateTree(node, buffer, ptr, file_len, dump_file);
        TEXT_DUMP(dump_file, buffer[*ptr], ptr, node, NULL, NULL, buffer);
        (*ptr)++;                                                           //закрываем )

        return node;
    }

    else if (buffer[*ptr] == ADD || buffer[*ptr] == SUB || buffer[*ptr] == MUL || buffer[*ptr] == DIV)
    {
        node = CreateNode(buffer[*ptr], OP, NULL, NULL);

        (*ptr)++;
        node->left  = CreateTree(node->left,   buffer, ptr, file_len, dump_file);
        node->right = CreateTree(node->right,  buffer, ptr, file_len, dump_file);
        TEXT_DUMP(dump_file, buffer[*ptr], ptr, node, node->left, node->right, buffer);

        return node;
    }

    else if (buffer[*ptr] == X || buffer[*ptr] == Y)
    {
        temp_node = CreateNode(X, VAR, NULL, NULL);
        TEXT_DUMP(dump_file, buffer[*ptr], ptr, temp_node, temp_node->left, temp_node->right, buffer);
        (*ptr)++;

        return temp_node;
    }

    else if ('0' <= buffer[*ptr] && buffer[*ptr] <= '9')
    {
        char temp_str[LENGTH_LINE] = {0};
        int i = 0;

        while ('0' <= buffer[*ptr] && buffer[*ptr] <= '9')
        {
            assert(0 <= *ptr && *ptr < file_len - 1);

            temp_str[i] = buffer[*ptr];
            (*ptr)++;
            i++;
        }

        temp_str[i] = '\0';
        long value = strtol(temp_str, NULL, 10);
        if (value == 0)
            fprintf(stderr, "[ERROR] %s:%d %s() Empty line in strtol() \n", __FILE__, __LINE__, __func__);

        temp_node= CreateNode(value, NUM, NULL, NULL);
        TEXT_DUMP(dump_file, buffer[*ptr], ptr, temp_node, temp_node->left, temp_node->right, buffer);

        return temp_node;
    }

    else
    {
        fprintf(stderr, "[ERROR] %s:%d %s() Incorrect Expression [\"%s\", character \"%c\"] \n", __FILE__, __LINE__, __func__, buffer, buffer[*ptr]);
        return NULL;        //assert(0);
    }
}