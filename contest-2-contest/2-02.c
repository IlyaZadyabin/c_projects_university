#include <stdio.h>
int main(void)
{
    int a[10001], b[10001];
    int Na, Nb, x,i;
    Na = Nb = 0;
    x = 1;

    for(i = 0; x != 0; i++)
    {
        scanf("%d", &x);

        if(i%2 == 0)
        {
            b[Nb] = x;
            Nb++;
        }
        else
        {
            a[Na] = x;
            Na++;
        }
    }

    for(i = 0; i<Nb; i++)
    {
        if (b[i] != 0)
        {
            printf("%d ", b[i]);
        }
    }

    for(i=Na-1; i!=-1; i--)
    {
        if(a[i] != 0)
        {
            printf("%d ", a[i]);
        }
    }
}
