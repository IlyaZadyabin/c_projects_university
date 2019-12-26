#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int
main(int argc, char *argv[]) 
{
    double percent = 0, rate = atof(argv[1]);
    int i;

    for(i = 2; i < argc; i++) {
        percent = atof(argv[i]);
        rate *= (percent + 100) / 100;
        rate *= 10000, rate = round(rate), rate /= 10000;
    }
    printf("%.4lf\n", rate);
}
