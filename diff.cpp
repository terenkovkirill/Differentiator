#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "diff.h"

Node_t* NewNode(Node_t* node, int type, int value)
{
    Node_t* node = (Node_t *)calloc(1, sizeof(Node_t));

    node->type = type;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
}

//=====================================================================

Node_t* ReadExpression(const char* file)
{
    FILE* file_ptr = fopen(file, "rb");
    
    if (file_ptr == NULL) 
        printf(" \n ERROR file pointer = NULL:   Line %d, Function %s \n", __LINE__, __func__);

    struct stat file_data = {};
    if (fstat(fileno(file_ptr), &file_data) != 0)
        printf(" \n ERROR Couldn`t retrieve length of the file:   Line %d, Function %s \n", __LINE__, __func__);
    int file_len = file_data.st_size;

    char* buffer = (char *)calloc(file_len, sizeof(char));
    if (!buffer)
    {
        printf(" \n ERROR Failed to allocate buffer memory:   Line %d, Function %s \n", __LINE__, __func__);
    }

    int read_count = fread(buffer, sizeof(char), file_len, file_ptr);
    if (read_count != file_len)
    {
        printf(" \n ERROR Failed to read file:   Line %d, Function %s \n", __LINE__, __func__);
    }

    fclose(file_ptr);
    
    return CreatTree(buffer);
}

//=====================================================================

Node_t* CreatTree(char *buffer)