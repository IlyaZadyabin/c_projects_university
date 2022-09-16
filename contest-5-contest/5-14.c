#include <stdio.h>
#include <malloc.h>

int is_prime(int n)
{
    int i;

    for(i = 2; i*i <= n; i++)
    {
        if(n % i == 0)
            return 0;
    }
    return 1;
}

void find_prime(int n, int figure)
{
    int flag = 0;
    
    if(figure > 0)
    {
        if(is_prime(n*10 + 1))
            find_prime(n*10 + 1, figure - 1);

        if(is_prime(n*10 + 3))
            find_prime(n*10 + 3, figure - 1);

        if(is_prime(n*10 + 7))
            find_prime(n*10 + 7, figure - 1);

        if(is_prime(n*10 + 9))
            find_prime(n*10 + 9, figure - 1);
        flag = 1;
    }
    if (flag == 0)
        printf("%d ", n);
}


int main(void)
{
    int N, i;
    scanf("%d", &N);

    for(i = 2; i < 10; i++)
    {
        if(is_prime(i))
        {
            if(N == 1)
               printf("%d ", i);
            else
                find_prime(i, N-1);
        }
    }
}
