#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

void PrintMtx(int n, long long int matr[n][n+1])
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n + 1; j++)
            printf("%lli ", matr[i][j]);
        printf("\n");
    }
}

void SetMtx(int n, long long int matr[n][n+1])
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n + 1; j++)
            scanf("%lli", &matr[i][j]);
}

void swap(int n, long long int matr[n][n+1], int row1, int row2)
{
    int tmp;
    int i;

    for(i = 0; i < n + 1; i++ )
    {
        tmp = matr[row1][i];
        matr[row1][i] = matr[row2][i];
        matr[row2][i] = tmp;
    }
}

long long int GCD (long long int a, long long int b)
{
    int tmp;

	while (b)
    {
		a %= b;
        tmp = a;
        a = b;
        b = tmp;
	}
	return a;
}

void reduce(int n, long long int matr[n][n+1], int i)
{
    long long int gcd;
    int j;
    gcd = 1;

    for(j = 0; j < n+1; j++)
    {
        if(matr[i][j])
        {
            gcd = matr[i][j];
            break;
        }
    }

    for(j = j + 1; j < n+1; j++)
        gcd = GCD(gcd, matr[i][j]);

    if(gcd && (gcd != 1))
        for(j = 0; j < n+1; j++)
            matr[i][j] /= gcd;
}

void Gauss(int n, long long int matr[n][n+1])
{
    int t, j, i, number_found, main_elem, below_elem;
    number_found = 0;

    for(t = 0; t < n - 1; t ++)
    {
        for(i = t; i < n; i++)
        {
            if(matr[i][t] != 0)
            {
                if(i != t) swap(n, matr, i, t);

                number_found = 1;
                break;
            }
            else number_found = 0;
        }

        if(!number_found) continue;

        for(i = t+1; i < n; i++)
        {
            main_elem = matr[t][t];
            below_elem = matr[i][t];

            if(!below_elem) continue;

            for(j = t; j < n + 1; j++)
            {
                matr[t][j] *= below_elem;
                matr[i][j] *= main_elem;
                matr[i][j] -= matr[t][j];
                matr[t][j] /= below_elem;
            }
            reduce(n, matr, i);
        }
    }

    for(t = n-1; t >= 0; t --)
    {
        for(i = t; i >= 0; i--)
        {
            if(matr[i][t] != 0)
            {
                if(i != t) swap(n, matr, i, t);

                number_found = 1;
                break;
            }
            else number_found = 0;
        }

        if(!number_found) continue;

        for(i = t-1; i >= 0; i--)
        {
            main_elem = matr[t][t];
            below_elem = matr[i][t];

            if(!below_elem) continue;

            for(j = n; j >= 0; j--)
            {
                matr[t][j] *= below_elem;
                matr[i][j] *= main_elem;
                matr[i][j] -= matr[t][j];
                matr[t][j] /= below_elem;
            }
            reduce(n, matr, i);
        }
    }
}


void printf_answers(int n, long long int matr[n][n+1])
{
    int i;

    for(i = 0; i < n; i++)
        printf("%lli\n", (matr[i][n] / matr[i][i]) );
}


int main(void)
{
    int n;
    scanf("%d", &n);

    long long int matr[n][n+1];

    SetMtx(n, matr);
    Gauss(n, matr);
    printf_answers(n, matr);

}
