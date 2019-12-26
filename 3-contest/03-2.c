#include <stdio.h>
#include <stdlib.h>

int 
main(int argc, char *argv[])
{
    long long neg = 0, pos = 0, num = 0;
    int i;
    char *ptr;

    for(i = 1; i < argc; i++) {
        num = strtoll(argv[i], &ptr, 10);
        if(num < 0) {
            neg += num;
        }

        if(num > 0) {
            pos += num;
        }
    }

    printf("%lld\n%lld\n", pos, neg);
}
