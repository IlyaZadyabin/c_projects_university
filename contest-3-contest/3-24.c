#include <stdio.h>

int min(long long int a, long long int b)
{
    long long int min;
    min = (a < b) ? a : b;
    return min;
}

int lighten(int N)
{
    int i, lighten, i_prev, x_prev, l_prev;
    long long int x;

    lighten = 0;
    i_prev = -1;
    x_prev = 0;
    l_prev = 1;

    for(i = 0; i <= N; i++)
    {
        if(i != N)
            scanf("%lli", &x);
        else
            x = 1;

        if (x > 0)
        {
            if(x_prev > 0)
                lighten += min(i - i_prev - 1, x_prev);

            lighten += (l_prev = (x_prev >= i - i_prev));

            x_prev = x;
            i_prev = i;
        }

        if(x < 0)
        {
            if(x_prev > 0)
            {
                lighten += min(i - i_prev - 1, -x + x_prev);

                lighten += (!l_prev && (-x >= i - i_prev));

                lighten += (l_prev = (x_prev >= i-i_prev));
            }
            else
            {
                lighten += min(i - i_prev - 1, -x);

                lighten += ( (-x >= i - i_prev) && !l_prev);

                l_prev = 0;
            }
            x_prev = x;
            i_prev = i;
        }
    }

    lighten -= l_prev;
    return lighten;
}

int main(void)
{
    int N;
    scanf("%d", &N);
    printf("%d", lighten(N) );
}
