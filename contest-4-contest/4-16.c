#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 4000001

int main(void)
{
    int j, k, i, final_pos, length;
    char *s;
    s = (char *) malloc(SIZE * sizeof(char));

    i = final_pos = 0;

    scanf ("%s", s);
    length = strlen(s);

    strcat (s, s);

    while (i < length)
    {
        final_pos = i;
        j = i + 1;
        k = i;

        while ((j < 2 * length) && (s[k] <= s[j]))
        {
            if (s[k] < s[j])
                k = i;
            else
                k++;
            j++;
        }
        while (i <= k)
            i += j - k;
    }

    for (i = final_pos; i < length + final_pos; i++)
        printf("%c", s[i]);

    free(s);
    return 0;
}
