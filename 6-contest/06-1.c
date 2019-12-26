#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

enum { FORMAT_SIZE = 10 };

int main(void)
{
    uint32_t i;
    int32_t j, n, w, flag = 0;
    scanf("%" SCNo32 "%" SCNo32, &n, &w);

    for(i = 0, j = 0; i < ((uint32_t) 1 << n); i++, j++) {
        printf("|%*"PRIo32"|", (int) w, i);
        printf("%*"PRIu32"|", (int) w, i);

        if(j < ((uint32_t) 1 << (n - 1)) && !flag) {
            printf("%*"PRId32"|", (int) w, j);
        } else {
            if(flag == 0) {
                j = 0;
            }
            flag = 1;

            printf("%*"PRId32"|", (int) w, -j);
        }
        printf("\n");
    }
}
