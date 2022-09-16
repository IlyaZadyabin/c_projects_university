#include <stdio.h>

int isprime(int N)
{
    if (N == 1)
        return 0;

    for(int i = 2; i*i <= N; i++)
    {
        if(N % i == 0)
        {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    int N;
    scanf("%d", &N);

    while(isprime(N) != 1)
        N++;
    
    printf("%d\n", N);
}
