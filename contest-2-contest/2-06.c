#include <stdio.h>
int main(void)
{
    int N, i, j;
    scanf("%d", &N);
    int a[N], b[N];

    for(i = 0; i < N; i++)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    for (j = 0; j != 2; j++)
    {
        for(i = 0; i < N; i++)
            b[i] = a[b[i]-1];
    }

    for(i = 0; i < N; i++)
        printf("%d ", b[i]);
}
