#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "diff.h"
#include "RecursiveDescent.h"


Node_t* NewNode(int type, int value, Node_t* left, Node_t* right)
{
    Node_t* node = (Node_t *)calloc(1, sizeof(Node_t));

    node->type = type;
    node->value = value;
    node->left = left;
    node->right = right;

    return node;
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
                            node, node->value, node->left, node->right); // left_node[style=filled, fillcolor = "red"]


    if (node->left) 
    {
        fprintf(graf_dump, "node%p -> node%p;\n", node, node->left);
        PreorderTraversal(node->left, graf_dump);
    }

    if (node->right)
    {
        fprintf(graf_dump, "node%p -> node%p;\n", node, node->right);
        PreorderTraversal(node->right, graf_dump);
    }

    return 0;
}

//=====================================================================

Node_t* diff(Node_t* node)
{
    if (node->type == NUM)
        return NewNode(NUM, node->value, NULL, NULL);
    
    if (node->type == VAR)
        return NewNode(VAR, node->value, NULL, NULL);
    
    if (node->type == OP)
    {
        switch(node->value)
        {
            case ADD:
                return NewNode(OP, ADD, diff(node->left), diff(node->right));

            case MUL:
            {
                Node_t* dL = diff(node->left), *dR = diff(node->right);
                Node_t* cL = copy(node->left), *cR = copy(node->right);
                
                return NewNode(OP, ADD, NewNode(OP, MUL, dL, cR), NewNode(OP, MULL, cL, dR));
            }

            //TODO: добавить сюда ещё кучу (19 - 2) case
        }
    }
    
}

/*Миша:         The term 'run' is not recognized....
                Нужно ли, чтобы 2 последние функции возвращали нули?
                ?? по реализации дифферециатора
*/