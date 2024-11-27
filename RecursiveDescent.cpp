#include <stdio.h>

int GetG(int p, char* s);
int GetN(int p, char* s);
int GetE(int p, char* s);
int GetP(int p, char* s);
void SyntaxError();

int main()
{
    char s[] = "25*10*(3*(25-10*2)+1)";
    int p = 0;
    int result  = GetG(p, s);
    
    if (result != 0)
        printf("It works \n");
}

int GetG(int p, char* s)
{
    int val = GetN(p, s);
    if (s[p] != '$')
        SyntaxError();
    p++;
    return val;
}


int GetN(int p, char* s)
{
    int val = 0;
    int old_p = p;
    while (('0' <= s[p]) && (s[p] <= '9'))
    {
        val = val * 10 + s[p] - '0';
        p++;
    }

    if (old_p == p)
    {
        SyntaxError();
    }

    return val;
}

int GetE(int p, char* s)
{
    int val = GetN(p, s);
    while (s[p] == '+' || s[p] == '-')
    {    
        int op = s[p];
        p++;
        int val2 = GetN(p, s);
        if (op == '+')
            val += val2;
        else
            val -= val2;
    }

    return val;
}

int GetP(int p, char* s)
{
    if(s[p] == '(')
    {
        int val = GetE(p, s);

        if (s[p] == ')')
            SyntaxError();

        p++;
        return val;
    }

    else 
        return GetN(p, s);
}



void SyntaxError()
{
    printf("ERROR: Error in input data \n");
}