#include "ExpressionTree.h"
#include <assert.h>

CodeError TextDump(FILE* dump_file, char value, int* ptr, Node_t* node, Node_t* left, Node_t* right, char* buffer, const char* file, int line, const char* func)
{
    if (buffer == NULL) 
    {
        printf("Null poiter of buffer \n"
               "called from %s:%d %s\n"
               "address buffer = %p \n", file, line, func, buffer);
        return NULL_PTR;
    }

    fprintf(
        dump_file,
        "Case \"%c\" \n"
        "called from %s:%d %s() \n"
        "{ \n"
        "   buffer[*ptr] = buffer[%d] = \"%c\" \n"
        "   ptr = %p \n"
        "   node = %p \n"
        "   node->left = %p"
        "   node->right = %p"
        "   buffer: \"%s\" \n"
        "} \n\n\n",
        value, file, line, func, *ptr, buffer[*ptr], ptr, node, node->left, node->right, buffer
    );

    return OK;
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

            else if (node->value == Y)
                fprintf(file, "     node%p[shape=\"circle\", style=\"filled\", fillcolor=\"#FFA07A\", width = 0.8, height = 0.8, label=\"%c\"] \n", node, node->value);

            break;

        case OP:
            fprintf(file, "     node%p[shape=\"circle\", style=\"filled\", fillcolor=\"#87CEEB\", width = 0.8, height = 0.8, label=\"%c\"] \n", node, node->value);
            break;
        
        default:
            fprintf(stderr, "[ERROR] %s:%d %s() Incorrect node->type \n", __FILE__, __LINE__, __func__);
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