#include <stdio.h>
#include <math.h>

float size(float x1, float y1, float x2, float y2)
{
    return sqrt( pow((x2 - x1), 2) + pow((y2 - y1), 2) );
}

void med(float Xa, float Ya, float Xb, float Yb, float Xc, float Yc)
{
    float Xm, Ym, k;

    k = size(Xa, Ya, Xb, Yb) / size(Xa, Ya, Xc, Yc);

    Xm = Xb + k*(Xc - Xb)/(k+1);
    Ym = Yb + k*(Yc - Yb)/(k+1);

    printf("%.5f %.5f\n", Xm, Ym);
}

int main(void)
{
    float Xa, Ya, Xb, Yb, Xc, Yc;
    scanf ("%f%f", &Xa, &Ya);
    scanf ("%f%f", &Xb, &Yb);
    scanf ("%f%f", &Xc, &Yc);

    med(Xc, Yc, Xa, Ya, Xb, Yb); // ACB
    med(Xa, Ya, Xb, Yb, Xc, Yc); // BAC
    med(Xb, Yb, Xc, Yc, Xa, Ya); // ABC
}
