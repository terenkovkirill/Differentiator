#include <TXLib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "diff.h"
#include "RecursiveDescent.h"


Node_t* NewNode(int type, int value, Node_t* left, Node_t* right)
{
    assert(left != NULL);
    assert(right != NULL);

    Node_t* node = (Node_t *)calloc(1, sizeof(Node_t));

    node->type = type;
    node->value = value;
    node->left = left;
    node->right = right;

    return node;
}

//=====================================================================

struct ArgRec ReadExpression(const char* file)          //Можно возвращать указатель на структуру
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
    
    struct ArgRec arg_rec;
    arg_rec.p = 0;
    arg_rec.s = buffer;
    
    return arg_rec;
}

//=====================================================================

int GrafDump(Node_t* node)
{
    assert(node != NULL);

    FILE* graf_dump = fopen("graf_dump.dot", "w");
    if (graf_dump == NULL)
    {
        printf("Unable to open file \"garf_dump.dot\" \n");
        return -1;
    }

    fprintf(graf_dump, "strict digraph \n { \n");                       //строгий (одно ребро между 2 узлами) ориентированный граф
    fprintf(graf_dump, "rankdir = \"TB\"; \n \n");                      //начальная ориентация сверху вниз
    fprintf(graf_dump, "node[shape = Mrecord]; \n");                     //форма для записи (закруглённые узлы)

    PreorderTraversal(node, graf_dump);

    fprintf(graf_dump, "}");

    fclose(graf_dump);
    system("dot graf_dump.dot -T png -o graf_dump.png");    

    return 0;
}

//=====================================================================

int PreorderTraversal(Node_t* node, FILE* graf_dump)
{
    assert(node != NULL);
    assert(graf_dump != NULL);

    if (node->type == NUM)
        fprintf(graf_dump, "node%p[style = filled, fillcolor = \"#40e0d0\", label = \"{type = num | value = %d | {LEFT = %p | RIGHT = %p}}\" ];\n", 
                            node, node->value, node->left, node->right);                            //зачем здесь left и right ? 

    else if (node->type == OP)
        fprintf(graf_dump, "node%p[style = filled, fillcolor = \"#a0522d\", label = \"{type = op  | value = %d \\n (OpType) | {LEFT = %p | RIGHT = %p}}\" ];\n", 
                            node, node->value, node->left, node->right);
    
    else 
        fprintf(graf_dump, "node%p[style = filled, fillcolor = \"#ff0000\", label = \"{type = var | value = %d \\n (NumVar)| {LEFT = %p | RIGHT = %p}}\" ];\n", 
                            node, node->value, node->left, node->right);


    if (node->left)
        fprintf(graf_dump, "node%p -> node%p;\n", node, node->left);
        PreorderTraversal(node->left, graf_dump);

    if (node->right)
        fprintf(graf_dump, "node%p -> node%p;\n", node, node->right);
        PreorderTraversal(node->right, graf_dump);

    return 0;
}


/*Миша:         The term 'run' is not recognized....
                Нужно ли, чтобы 2 последние функции возвращали нули?
                ?? по реализации дифферециатора
*/