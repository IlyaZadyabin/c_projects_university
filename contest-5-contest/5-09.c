#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct coord
{
    int x;
    int y;
};

int distance(int x1, int y1, int x2, int y2)
{
    return abs(x2-x1) + abs(y2-y1);
}

int main(void)
{

    int M, N, k, i, j, t;
    int cur_distance, min_distance, max_distance;
    max_distance = 0;
    min_distance = 10000;

    scanf("%d %d %d", &N, &M, &k);
    struct coord viruses[k];

    for(i = 0; i < k; i++)
    {
        scanf("%d %d", &viruses[i].x, &viruses[i].y);
    }

    for(i = 1; i <= N; i++)
    {
        for(j = 1; j <= M; j++)
        {
            for(t = 0; t < k; t++)
            {
                cur_distance = distance(j, i, viruses[t].x, viruses[t].y);
                if (cur_distance < min_distance)
                    min_distance = cur_distance;
            }

            if(min_distance > max_distance)
                max_distance = min_distance;

            min_distance = 10000;
        }
    }

    printf("%d", max_distance);

    return 0;
}
