#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x, y, place, down, up, left, right, count, start;

    place = down = up = left = right = count = start = 0;
    scanf("%d%d", &x, &y);

    if (abs(x) > abs(y)) start = 1;


    while ((x != 0) || (y != 0))
    {
        if ((x>0) && (y>=0)) place = 1;

        if ((x<=0) && (y>0)) place = 2;

        if ((x<0) && (y<=0)) place = 3;

        if ((x>=0) && (y<0)) place = 4;

        if (place == 1)
        {
            if (start == 1)
            {
                x -= 1;
                down = 0;
                up = 0;
                right = 0;
                left = 1;
                start = 0;
            }
            else
            {
                if((down == 1) || (up == 1))
                {
                    x -= 1;
                    down = 0;
                    up = 0;
                    right = 0;
                    left = 1;
                }
                else
                {
                    y -= 1;
                    down = 1;
                    up = 0;
                    right = 0;
                    left = 0;
                }
            }

            count ++;
            place = 0;
        }

        if (place == 2)
        {

            if (start == 1)
            {
                x += 1;
                down = 0;
                up = 0;
                right = 1;
                left = 0;
                start = 0;
            }
            else
            {
                if((down == 1) || (up == 1))
                {
                    x += 1;
                    down = 0;
                    up = 0;
                    right = 1;
                    left = 0;
                }
                else
                {
                    y -= 1;
                    down = 1;
                    up = 0;
                    right = 0;
                    left = 0;
                }
            }

            count ++;
            place = 0;
        }

        if (place == 3)
        {
            if (start == 1)
            {
                x += 1;
                down = 0;
                up = 0;
                right = 1;
                left = 0;
                start = 0;
            }
            else
            {
                if((down == 1) || (up == 1))
                {
                    x += 1;
                    down = 0;
                    up = 0;
                    right = 1;
                    left = 0;
                }
                else
                {
                    y += 1;
                    down = 0;
                    up = 1;
                    right = 0;
                    left = 0;
                }
            }

            count ++;
            place = 0;
        }

        if (place == 4)
        {
            if (start == 1)
            {
                x -= 1;
                down = 0;
                up = 0;
                right = 0;
                left = 1;
                start = 0;
            }
            else
            {
                if((down == 1) || (up == 1))
                {
                    x -= 1;
                    down = 0;
                    up = 0;
                    right = 0;
                    left = 1;
                }
                else
                {
                    y += 1;
                    down = 0;
                    up = 1;
                    right = 0;
                    left = 0;
                }
            }

            count ++;
            place = 0;
        }
    }

    printf("%d", count);
}
