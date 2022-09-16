#include <stdio.h>

int count[10001];

int main(void)
{
    int N, i, x, max, flag;
    

    flag = 1;
    max = 0;

    scanf("%d", &N);

    for(i = 0; i < N;i++)
    {
        scanf("%d", &x);
        if (x <= 0)
        {
            flag = 0;
            break;
        }

        if(x > max)
        {
            max = x;
        }
        count[x]++;
    }

    for(i = 1; i <= max; i++)
    {
        if ((count[i] > 1) || (count[i] == 0) )
        {
            flag = 0;
            break;
        }
    }

    if (flag == 1)
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }
}
