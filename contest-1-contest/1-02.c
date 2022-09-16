#include <stdio.h>
int main(void)
{
	int N, num, max,count;
	count = 1;

	scanf("%d", &N);
	scanf("%d", &max);

	for(int i = 0; i < N-1; i++)
	{
		scanf("%d", &num);
		if (num > max)
        {
            max = num;
            count = 1;
        }
        else
        {
            if(num == max)
            {
                count++;
            }
        }
	}
	printf("%d", count);
}
