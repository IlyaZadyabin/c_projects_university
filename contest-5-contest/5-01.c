#include <stdio.h>
#include <malloc.h>

struct matrix{
    long long int r;
    long long int i;
};

int main(void)
{
    int N, j, i;
    long long int a, b;
    scanf("%d", &N);

    struct matrix old_matrix[N][N];
    struct matrix new_matrix[N][N];

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            scanf("%lli", &a);
            scanf("%lli", &b);

            old_matrix[i][j].r = a;
            old_matrix[i][j].i = b;
        }
    }

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            new_matrix[i][j].r = old_matrix[j][i].r;
            new_matrix[i][j].i = -old_matrix[j][i].i;
        }
    }

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            printf("%lli ", new_matrix[i][j].r);
            printf("%lli ", new_matrix[i][j].i);
        }
        printf("\n");
    }

    return 0;
}
