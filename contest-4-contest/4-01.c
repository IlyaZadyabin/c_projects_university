#include <stdio.h>
#include <string.h>

#define SIZE 10002

void prefix_function (char *s, int *p, int n)
{
     int i;
     p[0] = 0;

     for (i = 1; i < n; i++)
     {
        int j = p[i-1];

        while ((j > 0) && (s[i] != s[j]))
             j = p[j-1];

        if (s[i] == s[j])
            j++;

        p[i] = j;
     }
}

void s_find(char *sub, char *s, int *p, int sub_size, int s_size)
{
    int n;

    n = sub_size + s_size + 1;

    char symbol[] = " ";
    char string[n];

    string[0] = 0;

    strcat(string, sub);
    strcat(string, symbol);
    strcat(string, s);

    prefix_function(string, p, n);

    printf("%d ", p[n-1]);
}

int main(void)
{
    int s1_size, s2_size;

    s1_size = s2_size = 0;

    int p[2*SIZE + 1];

    char s1[SIZE], s2[SIZE];

    fgets(s1, SIZE, stdin);
    fgets(s2, SIZE, stdin);

    s1_size = strlen(s1) - 1;
    s2_size = strlen(s2) - 1;

    s1[s1_size] = 0;
    s2[s2_size] = 0;

    s_find(s1, s2, p, s1_size, s2_size);
    s_find(s2, s1, p, s2_size, s1_size);
}
