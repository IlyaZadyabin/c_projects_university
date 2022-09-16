#include <stdio.h>
int N;

void mas_print(int a[], int n)
{
    int i;

    for(i = 0; i < n;i++ )
        printf("%d ", a[i]);
    printf("\n");
}

int ladder(int a[], int j, int K)
{
    int i, flag;
    flag = 0;

    for(i = j+1; i < K; i++)
    {
        flag = 1;
        if(a[i-1] + 1 > N-1)
        {
            flag = 0;
            break;
        }
        a[i] = a[i-1] + 1;
    }
    return (flag);
}

int main(void)
{
    int K, i;
    scanf("%d%d", &N, &K);
    int a[K];

    for(i = 0; i < K; i++)
        a[i] = i;

    mas_print(a, K);

    i = K-1;

    while(i >= 0)
    {
        if(a[i] != N-1)
        {
            if(i != K-1)
            {
                a[i]++;

                if(ladder(a, i ,K))
                {
                    mas_print(a, K);
                    i = K-1;
                }
                else
                    i--;
            }
            else
            {
                a[i]++;
                mas_print(a, K);
            }
        }
        else
            i--;
    }
}
