#include <stdio.h>
#include <string.h>

#define SIZE 102

int main(void)
{
    int L, i, count, f, s, t, hundred, ten, digit, number;
    char N[SIZE];
    count = 0;

    int mas[1000];

    for(i = 100; i < 1000; i++)
    {
        mas[i] = 0;
    }

    for(i = 100; i < 1000; i++)
    {
        mas[i] = 0;
    }

    fgets(N, SIZE, stdin);
    L = strlen(N) - 1;

    for(f = 0; f < L; f++)
    {
        hundred = (N[f] - '0') * 100;
        for(s = f + 1; s < L; s++)
        {
            ten = (N[s] - '0') * 10;
            for(t = s + 1; t < L; t++)
            {
                digit = (N[t] - '0');

                number = hundred + ten + digit;

                if(mas[number] != 1 && (number) >= 100)
                {
                    mas[number] = 1;
                    count++;
                }
            }
        }
    }

    printf("%d", count);
}
