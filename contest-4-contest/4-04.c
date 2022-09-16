#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define SIZE 1000002

int main(void)
{
    char s[SIZE];
    char x;
    int *even, *odd;
    even = (int*)malloc((SIZE+1) * sizeof(int));
    odd = (int*)malloc((SIZE+1) * sizeof(int));

    int N, i, odds, evens;

    odds = evens = 0;

    scanf("%c", &x);
    for(i = 1; x != '\n'; i++)
    {
        s[i] = x;
        scanf("%c", &x);
    }
    N = i-1;

    odd[N+1] = even[N+1] = 0;

    for(i = N; i >= 1; i--)
    {
        if (s[i] == 'A')
        {
            if(i % 2)
            {
                odd[i] += odd[i+1] + 1;
                even[i] = even[i+1];
            }
            else
            {
                even[i] += even[i+1] + 1 ;
                odd[i] = odd[i+1];
            }
        }
        else
        {
            odd[i] = odd[i+1];
            even[i] = even[i+1];
        }
    }

    for(i = 1; i < N; i++)
    {
        if(odds + even[i+1] == evens + odd[i+1])
            printf("%d ", i);

        if (s[i] == 'A')
        {
            odds += i % 2;
            evens += !(i % 2);
        }
    }

    if(odds == evens)
        printf("%d ", i);

    free(even);
    free(odd);
    return 0;
}
