#include <stdio.h>
#include <math.h>
int main(void)
{
    int i, n, j, m;
    long int s, ext;
    int x[10000], a[10000];

    s = 0;
    ext = 1;

    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    scanf("%d", &m);
    for(i = 0; i < m; i++)
    {
        scanf("%d", &x[i]);
    }

    for(j = m-1; j > -1; j--)
    {
        for(i = 0; i < n; i++)
        {
            s += a[i]*ext;
            ext *= x[j];
        }
        
        ext = 1;
        printf("%li ", s);
        s = 0;
    }
}
