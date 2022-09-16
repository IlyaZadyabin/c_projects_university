#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 102

int main(void)
{
    int N, i, prev, j, count;

    count = prev = 0;
    char s[SIZE];

    scanf("%d", &N);
    int num[N];
    char string[SIZE * N];
    string[0] = 0;

    for(i = 0; i < N; i++)
    {
        scanf("%d\n", &num[i]);
    }

    for(j = 0; j < N; j++)
    {
        fgets(s, SIZE, stdin);

        for(i = 0; s[i] != 0; i++)
        {
            if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' ||
                s[i] == 'o' || s[i] == 'u' || s[i] == 'y' ||
                s[i] == 'A' || s[i] == 'E' || s[i] == 'I' ||
                s[i] == 'O' || s[i] == 'U' || s[i] == 'Y' )
            {
                if(prev == 0)
                    count++;
                prev = 1;
            }
            else
                prev = 0;
        }

        if (count == num[j])
            strcat(string, s);

        count = 0;
        prev = 0;
    }
    puts(string);
}
