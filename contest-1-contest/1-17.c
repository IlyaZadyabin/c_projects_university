#include <stdio.h>
int main(void)
{
    int N,s,x,i;
    s = 0;
    scanf("%d", &N);

    for(i = 0; i < N; i++)
    {
        scanf("%d", &x);
        s = s^x;
    }
    printf("%d",s);
}
