#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define SIZE 1000002

int prefix_function (char *s, int *p, int n, int *out)
{
    int i, k = 0;
    p[0] = 0;

    for (i = 1; i < n; i++)
    {
        int j = p[i-1];

        if(i == n-1)
        {
            while (j > 0)
            {
                if (s[i] == s[j])
                {
                    out[k] = n - (j+1);
                    k++;
                }
                j = p[j-1];
            }

            if (s[i] == s[j])
                j++;

            out[k] = n - j;
            break;
        }

        while ((j > 0) && (s[i] != s[j]))
            j = p[j-1];

        if (s[i] == s[j])
            j++;

        p[i] = j;
    }
    return k;
}

int main(void)
{
    int i, k;
    char s[SIZE];
    int *p;
    int *out;
    p = (int*) malloc(SIZE * sizeof(int));
    out = (int*) malloc(SIZE * sizeof(int));

    scanf("%s", s);
    size_t n = strlen(s);

    if(n == 1)
        printf("1");
    else
    {
        k = prefix_function(s, p, n, out);

        for(i = 0; i<= k; i++)
            printf("%d ", out[i]);

        if(out[k] != n)
            printf("%lu", n);
    }

    free(p);
    free(out);
}
