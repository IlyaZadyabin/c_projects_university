#include <stdio.h>
#include <math.h>
int main(void)
{
    double a, b, c, d, tmp;
    scanf("%lf%lf%lf%lf", &a, &b, &c, &d);

    if(d > c)
    {
        tmp = c;
        c = d;
        d = tmp;
    }

    if(b > a)
    {
        tmp = a;
        a = b;
        b = tmp;
    }

    if((c <= a) && (d <= b))
    {
        printf("YES");
    }
    else if ( (c > a) && (b >= (((pow(c,2) - pow(d,2))*sqrt(pow(c,2) - pow(a,2) + pow(d,2) ) + 2*c*d*a)/(pow(c,2) + pow(d,2))   ) ))
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }

}
