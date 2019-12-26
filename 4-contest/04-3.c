#include <stdio.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

enum { SIZE = 1024, MANTISSA_SIZE = 23 };

int
is_precise(unsigned int n)
{
    int left_bit_idx = -1, right_bit_idx = -1; 
    for(int i = 0; n; i++) {
        if(n & 1 && right_bit_idx == -1) {
            right_bit_idx = i;
            left_bit_idx = i;
        } else if(n & 1) {
            left_bit_idx = i;
        }
        n >>= 1;
    }
    return (left_bit_idx - right_bit_idx) <= MANTISSA_SIZE;
}

int
main(void)
{
    unsigned int num;

    while(fscanf(stdin, "%11u", &num) > 0) {
        printf("%d\n", is_precise(num));
    }
    return 0;
}
