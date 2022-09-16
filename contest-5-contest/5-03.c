#include <stdio.h>
#include <malloc.h>

int main(void)
{
    int i,count, x;
    count = 0;
    int *numbers = (int*) malloc(2 * sizeof(int));

    scanf("%d", &x);

    for(i = 0; x != 0; i++)
    {
        numbers[i] = x;
        count++;
        numbers = (int*)realloc(numbers, 2 * count * sizeof(int));
        scanf("%d", &x);
    }

    for(i = 0; i < count; i++)
        if(!(i%2))
            printf("%d ", numbers[i]);

    for(i = 0; i < count; i++)
        if(i%2)
            printf("%d ", numbers[i]);
    
    free(numbers);
}
