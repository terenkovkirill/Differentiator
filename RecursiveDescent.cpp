#include <stdio.h>

struct ArgRecursion
{
    int p;
    const char *s;
};

//const char* s = "7-2";

int GetG(ArgRecursion* arg_rec);
int GetN(ArgRecursion* arg_rec);
int GetE(ArgRecursion* arg_rec);
int GetP(ArgRecursion* arg_rec);
int GetT(ArgRecursion* arg_rec);
void SyntaxError();


//char s[] = "25*10*(3*(25-10*2)+1)";
//char s[] = "25 * 10 * (3 * (25 - 10 * 2) + 1) $";

int main()
{
    struct ArgRecursion arg_rec = {0,"25*10*(3*(25-10*2)+1)$"};
    //arg_rec.s = "77-8";
    //arg_rec.s = "25*10*(3*(25-10)*2)+1)";
    arg_rec.p = 0;
    //printf("Called from function %s line %d \n", __func__, __LINE__);
    int result  = GetG(&arg_rec);
    printf("s[p] = %c  Called from function %s line %d \n", arg_rec.s[arg_rec.p], __func__, __LINE__);
    if (result != 0)
        printf("It works \n");
    printf("result = %d", result);



    // printf("\n df;jsjnj; \n");
    // printf("%d \n", '*');
    // printf("%c", 1);

    return 0;
}

int GetG(ArgRecursion* arg_rec)
{
    printf("I was called from function %s line %d \n", __func__, __LINE__);
    int val = GetE(arg_rec);
    printf("s[p] = '%c' (char) \n", arg_rec->s[arg_rec->p]);
    if (arg_rec->s[arg_rec->p] != '$')
    {
        printf("Called SyntaxError in function %s line %d \n", __func__, __LINE__);
        SyntaxError();
    }
    arg_rec->p++;
    return val;
}


int GetN(ArgRecursion* arg_rec)
{
    //printf("I was called from function %s line %d \n", __func__, __LINE__);
    int val = 0;
    int old_p = arg_rec->p;
    printf("s[p] = %c  Called from function %s line %d \n", arg_rec->s[arg_rec->p], __func__, __LINE__);
    while (('0' <= arg_rec->s[arg_rec->p]) && (arg_rec->s[arg_rec->p] <= '9'))
    {
        val = val * 10 + arg_rec->s[arg_rec->p] - '0';
        arg_rec->p++;
        printf("s[p] = %c \n", arg_rec->s[arg_rec->p]);
        printf("$ in cycle in function GetN? \n");
    }

    if (old_p == arg_rec->p)
    {
        printf("Called SyntaxError in function %s line %d \n", __func__, __LINE__);
        SyntaxError();
    }

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
    while (arg_rec->s[arg_rec->p] == '*' || arg_rec->s[arg_rec->p] == '/')
    {
        int op = arg_rec->s[arg_rec->p];
        arg_rec->p++;
        int val2 = GetP(arg_rec);
        if (op == '*')
            val *= val2;
        else 
            val /= val2;
    }
    printf("%d line: %d\n", val, __LINE__);

    return val;
}

int GetP(ArgRecursion* arg_rec)
{
    printf("I was called from function %s line %d , s[p] = %c \n", __func__, __LINE__, arg_rec->s[arg_rec->p]);
    if(arg_rec->s[arg_rec->p] == '(')
    {
        arg_rec->p++;
        int val = GetE(arg_rec);

        if (arg_rec->s[arg_rec->p] != ')')
        {
            printf("Called SyntaxError in function %s line %d \n", __func__, __LINE__);
            SyntaxError();
        }

        printf("1 case in GetP before p++: '%d' \n", arg_rec->s[arg_rec->p]);
        arg_rec->p++;
        printf("2 case in GetP after p++: '%c' \n", arg_rec->s[arg_rec->p]);

        return val;
    }

    else 
        return GetN(arg_rec);
}



void SyntaxError()
{
    printf("ERROR: Error in input data \n");
}

