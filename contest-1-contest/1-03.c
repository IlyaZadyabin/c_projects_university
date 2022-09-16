#include <stdio.h>
int main(void)
{
	int N;
    char letter;
    unsigned char p;

    scanf("%d", &N);

    for(int i = 0; letter != '.'; i++)
    {
        scanf("%c", &letter);

        if(letter > 'Z')
        {
            p = (letter + N - 97)%26 + 97;
        }
        else
        {
            if((letter == 32) || (letter == 46))
            {
                p = letter;
            }
            else
            {
                p = (letter + N - 65)%26 + 65;
            }
        }
        printf("%c", p);
    }
}
