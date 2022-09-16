#include <stdio.h>
int main(void)
{
	int N, first,num, max, min;
	scanf("%d", &N);
	scanf("%d", &first);
	max = first;
	min = first;

	for(int i = 0; i < N-1; i++)
	{
		scanf("%d", &num);
		if (num>max)
		{
			max = num;
		}
		if (num<min)
		{
			min = num;
		}
	}
	printf("%d", (max-min));
}
