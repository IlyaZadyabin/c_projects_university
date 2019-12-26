#include <stdio.h>
#include <stdint.h>

int32_t
satsum (int32_t v1, int32_t v2)
{
    int32_t ans = 0;
    int32_t max = (int32_t) ((uint32_t) (-1) >> 1);
    int32_t min = (int32_t) ((uint32_t) (-1) - max);

    if(__builtin_sadd_overflow(v1, v2, &ans)) {
        if (ans > 0) {
            return min;
        } else {
            return max;
        }
    }
    return ans;
}
