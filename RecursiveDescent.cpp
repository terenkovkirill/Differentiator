#include <TXLib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "RecursiveDescent.h"
#include "diff.h"

//const char* s = "7-2";


/* Grammar
G ::= E$
E ::= T{['+''-']T}*
T ::= P{['*''/']P}*
P ::= '('E')' | N
N ::= ['0'-'9']+
*/

//сигма+: "2 ^ 3", "2 ^ 3 + 1", "(2 + 3) ^ 4, "2 ^ (3 + 4)", "(1 + 3) ^ (3 + 4)"
//сигма-: "2^", "^2", "2 ^"


//char s[] = "25*10*(3*(25-10*2)+1)";
//char s[] = "25 * 10 * (3 * (25 - 10 * 2) + 1)$";


Node_t* GetG(ArgRec* arg_rec)
{
    assert(arg_rec != NULL);

    printf("I was called from function %s line %d \n", __func__, __LINE__);
    Node_t* val = GetE(arg_rec);
    printf("s[p] = '%c' (char) \n", arg_rec->s[arg_rec->p]);
    if (arg_rec->s[arg_rec->p] != '$')
    {
        SYNTAX_ERROR(DOES_NOT_PROCESS_ELEMENTS);
    }
    arg_rec->p++;
    return val;
}

//=====================================================================

Node_t* GetE(ArgRec* arg_rec)
{
    assert(arg_rec != NULL);

    printf("I was called from function %s line %d \n", __func__, __LINE__);
    Node_t* val = GetT(arg_rec);

    while (arg_rec->s[arg_rec->p] == '+' || arg_rec->s[arg_rec->p] == '-')
    {    
        int op = arg_rec->s[arg_rec->p];
        arg_rec->p++;

        Node_t* val2 = GetT(arg_rec);

        if (op == '+')
            val = NewNode(OP, ADD, val, val2);
        else
            val = NewNode(OP, SUB, val, val2);
    }

    return val;
}

//=====================================================================

Node_t* GetT(ArgRec* arg_rec)
{
    assert(arg_rec != NULL);
    printf("I was called from function %s line %d \n", __func__, __LINE__);

    Node_t* val = GetP(arg_rec);
    printf("GetT, Line %d, s[p] = '%c' \n", __LINE__, arg_rec->s[arg_rec->p]);

    while (arg_rec->s[arg_rec->p] == '*' || arg_rec->s[arg_rec->p] == '/')
    {
        int op = arg_rec->s[arg_rec->p];
        arg_rec->p++;
        Node_t* val2 = GetP(arg_rec);
        if (op == '*')
            val = NewNode(OP, MUL, val, val2);
        else 
            val = NewNode(OP, DIV, val, val2);
        
        printf("In cycle in GetT \n");
    }

    printf("%p line: %d\n", val, __LINE__);

    return val;
}

//=====================================================================

Node_t* GetP(ArgRec* arg_rec)
{
    assert(arg_rec != NULL);
    printf("I was called from function %s line %d , s[p] = %c \n", __func__, __LINE__, arg_rec->s[arg_rec->p]);

    if(arg_rec->s[arg_rec->p] == ' ')                                                                   //ПРОБЕЛЫ
    arg_rec->p++;

    if(arg_rec->s[arg_rec->p] == '(')
    {
        arg_rec->p++;
        Node_t* val = GetE(arg_rec);

        if (arg_rec->s[arg_rec->p] != ')')
        {
            printf("Called SyntaxError in function %s line %d \n", __func__, __LINE__);
            SYNTAX_ERROR(NO_CLOSING_PARANTHESIS);
        }

        printf("1 case in GetP before p++: '%d' \n", arg_rec->s[arg_rec->p]);
        arg_rec->p++;
        printf("2 case in GetP after p++: '%c' \n", arg_rec->s[arg_rec->p]);

        if(arg_rec->s[arg_rec->p] == ' ')                                                               //ПРОБЕЛЫ
            arg_rec->p++;

        return val;
    }

    else 
        return GetN(arg_rec);
}

//=====================================================================

Node_t* GetN(ArgRec* arg_rec)
{
    assert(arg_rec != NULL);
    
    if  (arg_rec->s[arg_rec->p] == ' ')                                                             //ПРОБЕЛЫ
        arg_rec->p++;   

    int val = 0;
    int old_p = arg_rec->p;

    printf("s[p] = '%c'  Called from function %s before cycle. Line %d \n", arg_rec->s[arg_rec->p], __func__, __LINE__);
    while (('0' <= arg_rec->s[arg_rec->p]) && (arg_rec->s[arg_rec->p] <= '9'))
    {
        val = val * 10 + arg_rec->s[arg_rec->p] - '0';
        arg_rec->p++;
        printf("s[p] = '%c' after cycle in function GetN \n", arg_rec->s[arg_rec->p]);
    }

    if (old_p == arg_rec->p)
    {
        SYNTAX_ERROR(DOES_NOT_PROCESS_ELEMENTS);
    }

    if (arg_rec->s[arg_rec->p] == ' ')                                                                //ПРОБЕЛЫ
        arg_rec->p++;
    
    printf("s[p] = %c in the end of function GetN \n", arg_rec->s[arg_rec->p]);

    return NewNode(NUM, val, NULL, NULL);
}


// int GetV(ArgRecursion* arg_rec)
// {
//     int old_p = arg_rec->p;

//     if (arg_rec->s[arg_rec->p] == ' ')
//     {
//         arg_rec->p++;
//     }
// }

//=====================================================================

int SyntaxError(int error, const char* func, int line)
{
    if (error == DOES_NOT_PROCESS_ELEMENTS)
    {
        printf("ERROR: Function %s doesn`t process elements. Line: %d \n", func, line);
        return DOES_NOT_PROCESS_ELEMENTS;
    }

    if (error == NO_CLOSING_PARANTHESIS)
    {
        printf("ERROR: no closing paranthesis. Func: %s. Line: %d \n", func, line);
        return NO_CLOSING_PARANTHESIS;
    }

    return 1;                                                                           //норма?
}

//===================================================

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

// int main()
// {
//     struct ArgRecursion arg_rec = {0,"25 * 10 * (3 * (25 - 10 * 2) + 1)$"};
//     //arg_rec.s = "77-8";
//     //arg_rec.s = "25*10*(3*(25-10)*2)+1)";

//     arg_rec.p = 0;
//     int result  = GetG(&arg_rec);
//     printf("s[p] = %c  Called from function %s line %d \n", arg_rec.s[arg_rec.p], __func__, __LINE__);
//     if (result != 0)
//         printf("It works \n");
//     printf("result = %d", result);

//     return 0;
// }