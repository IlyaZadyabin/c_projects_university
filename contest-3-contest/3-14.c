#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int is_queen_valid(int Xh, int Yh, int Xq, int Yq)
{
    return ( ((Xq == Xh + 2) && (Yq == Yh + 1 || Yq == Yh - 1 ) ) ||
             ((Xq == Xh - 2) && (Yq == Yh + 1 || Yq == Yh - 1 ) ) ||
             ((Yq == Yh + 2) && (Xq == Xh + 1 || Xq == Xh - 1 ) ) ||
             ((Yq == Yh - 2) && (Xq == Xh + 1 || Xq == Xh - 1 ) ) );
}

int is_horse_valid(int Xh, int Yh, int Xq, int Yq)
{
    return ( ((abs(Xh - Xq) == abs(Yh - Yq)) && (Xh != Xq) ) || ( (Xh == Xq) && (Yh != Yq) ) || ( (Yh == Yq) && (Xh != Xq) ) );
}

int main(void)
{
    int Xq, Yq, Xh, Yh, swap, cheat, Garik, Tolik, x;
    Xh = Yh = Xq = Yq = 1;
    Garik = Tolik = cheat = swap = 0;
    x = getchar();

    while(x != 'X')
    {
        if ( (swap == 0) && (x != '\n'))
        {
            Xq = x - 'A' + 1;
            Yq = getchar() - '0';

            if(Xq == 8 && Yq == 8)
                Garik = 1;

            if(is_queen_valid(Xh, Yh, Xq, Yq) == 0)
                cheat = 1;

            swap^=1;
        }
        else if (x != '\n')
        {
            Xh = x - 'A' + 1;
            Yh = getchar() - '0';

            if(Xh == 8 && Yh == 8)
                Tolik = 1;

            if(is_horse_valid(Xh, Yh, Xq, Yq) == 0)
                cheat = 1;

            swap^=1;
        }

        x = getchar();
    }

    if ((cheat == 1)  || (Garik == Tolik))
        printf("Cheaters");
    else if(Tolik == 1)
        printf("Tolik");
    else if(Garik == 1)
        printf("Garik");
    else
        printf("Cheaters");
}
