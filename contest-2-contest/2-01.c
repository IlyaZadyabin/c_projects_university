#include <stdio.h>
#include <math.h>
int main(void)
{
    int a[10001];
    int i, x;
    x = 1;

    for(i = 0; x != 0; i++)
    {
        scanf("%d", &x);
        a[i] = x;
    }

    for(i = i-2; i != -1;i--)
    {
        printf("%d ", a[i]);
    }
}
