#include <stdio.h>
#include <malloc.h>

int main(void)
{
    int i, count, x, ans;
    count = 0;
    ans = 0;
    int *numbers = (int*) malloc(2 * sizeof(int));

    scanf("%d", &x);

    for(i = 0; x != 0; i++)
    {
        numbers[i] = x;
        count++;
        numbers = (int*)realloc(numbers, 2 * count * sizeof(int));
        scanf("%d", &x);
    }

    for(i = 0; i < count-1; i++)
    {
        if(numbers[i] < numbers[count-1])
            ans++;
    }
    printf("%d", ans);
    
    free(numbers);
}
