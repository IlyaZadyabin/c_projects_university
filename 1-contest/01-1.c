#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int
main(void)
{
    long long int ans, ans1, ans2, a, b, remainder;
    scanf("%lld %lld", &a, &b);
    ans = 0;
    remainder = a % b;

    if (a < 0) {
        b = -b;
    }

    ans1 = a + b - remainder;
    ans2 = a - remainder;

    if (ans1 > INT_MAX || ans1 < INT_MIN || abs(a - ans1) > abs(a - ans2) ||
            (abs(a - ans1) == abs(a - ans2) && (ans2 > ans1))) {
        ans = ans2;
    } else { 
        ans = ans1;
    }
    
    printf("%lld\n", ans);

    return 0;    
}
