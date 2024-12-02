#include <stdio.h>
#include "RecursiveDescent.h"

//const char* s = "7-2";


/*
G ::= E$
E ::= T{['+''-']T}*
T ::= P{['*''/']P}*
P ::= '('E')' | N
N ::= ['0'-'9']+
V ::= 'X'
*/


//char s[] = "25*10*(3*(25-10*2)+1)";
//char s[] = "25 * 10 * (3 * (25 - 10 * 2) + 1)$";

int main()
{
    struct ArgRecursion arg_rec = {0,"25 * 10 * (3 * (25 - 10 * 2) + 1)$"};
    //arg_rec.s = "77-8";
    //arg_rec.s = "25*10*(3*(25-10)*2)+1)";

    arg_rec.p = 0;
    int result  = GetG(&arg_rec);
    printf("s[p] = %c  Called from function %s line %d \n", arg_rec.s[arg_rec.p], __func__, __LINE__);
    if (result != 0)
        printf("It works \n");
    printf("result = %d", result);

    return 0;
}

int GetG(ArgRecursion* arg_rec)
{
    printf("I was called from function %s line %d \n", __func__, __LINE__);
    int val = GetE(arg_rec);
    printf("s[p] = '%c' (char) \n", arg_rec->s[arg_rec->p]);
    if (arg_rec->s[arg_rec->p] != '$')
    {
        SYNTAX_ERROR(DOES_NOT_PROCESS_ELEMENTS);
    }
    arg_rec->p++;
    return val;
}


int GetE(ArgRecursion* arg_rec)
{
    printf("I was called from function %s line %d \n", __func__, __LINE__);
    int val = GetT(arg_rec);

    while (arg_rec->s[arg_rec->p] == '+' || arg_rec->s[arg_rec->p] == '-')
    {    
        int op = arg_rec->s[arg_rec->p];
        arg_rec->p++;

        int val2 = GetT(arg_rec);
        if (op == '+')
            val += val2;
        else
            val -= val2;
    }

    return val;
}

int GetT(ArgRecursion* arg_rec)
{
    printf("I was called from function %s line %d \n", __func__, __LINE__);

    int val = GetP(arg_rec);
    printf("GetT, Line %d, s[p] = '%c' \n", __LINE__, arg_rec->s[arg_rec->p]);

    while (arg_rec->s[arg_rec->p] == '*' || arg_rec->s[arg_rec->p] == '/')
    {
        int op = arg_rec->s[arg_rec->p];
        arg_rec->p++;
        int val2 = GetP(arg_rec);
        if (op == '*')
            val *= val2;
        else 
            val /= val2;
        
        printf("In cycle in GetT \n");
    }

    printf("%d line: %d\n", val, __LINE__);

    return val;
}

int GetP(ArgRecursion* arg_rec)
{
    printf("I was called from function %s line %d , s[p] = %c \n", __func__, __LINE__, arg_rec->s[arg_rec->p]);

    if(arg_rec->s[arg_rec->p] == ' ')                                                                   //ПРОБЕЛЫ
    arg_rec->p++;

    if(arg_rec->s[arg_rec->p] == '(')
    {
        arg_rec->p++;
        int val = GetE(arg_rec);

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


int GetN(ArgRecursion* arg_rec)
{
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

    return val;
}


// int GetV(ArgRecursion* arg_rec)
// {
//     int old_p = arg_rec->p;

//     if (arg_rec->s[arg_rec->p] == ' ')
//     {
//         arg_rec->p++;
//     }
// }


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