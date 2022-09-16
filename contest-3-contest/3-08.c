#include <stdio.h>

int med(int a, int b, int c)
{
    int t;

    if (c > b)
    {
        t = c;
        c = b;
        b = t;
    }

    if (b > a)
    {
        t = a;
        a = b;
        b = t;
    }

    if (c > b)
    {
        t = c;
        c = b;
        b = t;
    }
    return b;
}

void trans(int *a, int *b, int N)
{
    int i;

    if(N == 1) return;

    for (i = 0; i < N-2; i++)
    {
        b[i] = med(a[i],a[i+1],a[i+2]);
        a[i] = 0;
    }

    if (N != 3)
    {
        trans(b, a, N-2);
    }
}

int main(void)
{
    int N, i;
    scanf("%d", &N);
    int a[N], b[N];

    for (i = 0; i < N; i++)
    {
        scanf("%d", &a[i]);
    }

    trans(a, b, N);

    if (a[0] != 0)
        printf("%d", a[0]);
    else
        printf("%d", b[0]);
}
