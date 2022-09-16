#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int x, a, b, N;

    long long int max1, max2, min1, min2;
    max1 = max2 = min1 = min2 = 0;

    scanf("%d", &N);

    if(N == 2)
    {
        scanf("%d", &a);
        scanf("%d", &b);
        if (a > b)
        {
            printf("%d %d", b, a);
        }
        else
        {
            printf("%d %d", a, b);
        }
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            scanf("%d", &x);

            if(x <= 0)
            {
                if(x <= min1)
                {
                    min2 = min1;
                    min1 = x;
                }
                else if(x <= min2)
                {
                    min2 = x;
                }
            }
            if (x >= 0)
            {
                if(x >= max1)
                {
                    max2 = max1;
                    max1 = x;
                }
                else if (x >= max2)
                {
                    max2 = x;
                }
            }
        }

        if (max1*max2 > min1*min2)
        {
            printf("%lli %lli\n", max2, max1);
        }
        else
        {
            printf("%lli %lli\n", min1, min2);
        }
   }
}
