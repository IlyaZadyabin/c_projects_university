#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define SIZE 1000002

int main(void)
{
    int K, spaces, i, need, N, each_space, extra, j, each_loop;
    spaces = j = 0;
    char *s;
    char *string;
    s = (char*)malloc((SIZE) * sizeof(char));
    string = (char*)malloc((SIZE) * sizeof(char));


    scanf("%d\n", &K);

    fgets(s, SIZE, stdin);
    N = strlen(s) - 1;

    for(i = 0; i < N; i++)
        if(s[i] == ' ')
            spaces++;

    need = K - N;
    each_space = need / spaces;
    extra = need - spaces * each_space;

    each_loop = each_space;

    for(i = 0; i < K; i++, j++)
    {
        string[i] = s[j];

        if(s[j] == ' ')
        {
            while (each_loop != 0)
            {
                i++;
                string[i] = ' ';
                each_loop--;
            }
            if(extra)
            {
                i++;
                string[i] = ' ';
                extra--;
            }
            each_loop = each_space;
        }
    }
    string[i] = '\n';
    puts(string);

    free(s);
    free(string);
}
