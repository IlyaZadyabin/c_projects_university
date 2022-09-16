#include <stdio.h>
int main(void)
{
    int N, max1, max2, max3, x, tmp;
    scanf("%d", &N);
    scanf("%d", &max1);
    scanf("%d", &max2);
    scanf("%d", &max3);

    for(int i = 0; i < N-3; i++)
    {
        scanf("%d", &x);

        if(x >= max1)
        {
            max3 = max2;
            max2 = max1;
            max1 = x;
        }
        else
        {
            if(x >= max2)
            {
                max3 = max2;
                max2 = x;
            }
            else
            {
                if(x >= max3)
                {
                    max3 = x;
                }
            }
        }
    }

    if(max3 > max2)
    {
        tmp = max2;
        max2 = max3;
        max3 = tmp;
    }

    if(max2 > max1)
    {
        tmp = max1;
        max1 = max2;
        max2 = tmp;
    }

    if(max3 > max2)
    {
        tmp = max2;
        max2 = max3;
        max3 = tmp;
    }
    printf("%d %d %d", max1, max2, max3);
}
