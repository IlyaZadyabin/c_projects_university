#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 8

int desk[SIZE+2][SIZE+2];

int main(void)
{
    int i, count, m,j,x,y;
    char s[SIZE*SIZE*2 + 1];

    count = 0;
    fgets(s, SIZE*SIZE*2 + 1, stdin);
  
    for(i = 0; i < strlen(s) - 1; i+=2)
    {
        x = s[i] - 'a' + 1;
        y = s[i+1] - '0';

        for(j = y + 1;j >= y - 1; j--)
        {
            for(m = x-1;m <= x+1; m++)
            {
                desk[m][j] = 1;
            }
        }
    }

    for(j = 1;j <= SIZE; j++)
        for(m = 1;m <= SIZE; m++)
            if (desk[m][j] == 0)
                count++;
            
        
    
    printf("%d", count);

}
