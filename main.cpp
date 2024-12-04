#include <stdio.h>

#include "diff.h"
#include "RecursiveDescent.h"

int main(int argc, const char* argv[])  
{
    if (argc != 2)
    {
        printf("ERROR: Incorrect number of function arguments \n");
    }

    struct ArgRec arg_rec = ReadExpression(argv[1]);

    Node_t* root = GetG(&arg_rec);

    GrafDump(root);


}