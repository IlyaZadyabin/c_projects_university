#include <stdio.h>
#include <math.h>
int main(void)
{
    int i, N, bit, XOR, x, y;
    scanf("%d", &N);

    x = y = XOR = 0;
    int a[N];

    for (i = 0; i < N; i++)
    {
        scanf("%d", &a[i]);
        XOR ^= a[i];
    }

    bit = XOR & ~(XOR -1);

    for(i = 0; i < N;i++)
    {
        if(a[i] & bit)
        {
            x ^= a[i];
        }
        else
        {
            y ^= a[i];
        }
    }
    
    if (x > y)
    {
        printf("%d %d", y, x);
    }
    else
    {
        printf("%d %d", x, y);
    }
}
