#include <stdio.h>

int NOD(int a, int b)
{
    while( (a != 0) && (b != 0))
    {
        if (a > b)
        {
            a = a % b;
        }
        else
        {
            b = b % a;
        }
    }
    return(a + b);
}

int main(void)
{
    int a, b, c, d, x, y;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    x = NOD(a,b);
    y = NOD(c,d);
    printf("%d", NOD(x, y));
}
