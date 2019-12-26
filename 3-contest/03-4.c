#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>  
#include <string.h>

enum { BUF_SIZE = 16 };

int 
main(void)
{
    int i, amount;
    unsigned long long res = 0, sign = 1, ans = 0;
    char number[BUF_SIZE];

    while((amount = read(0, number, sizeof(number))) > 0) {
        for(i = 0; i < amount; i++) {
            if(number[i] == '-') {
                sign = -1;
            } else if(number[i] == '+') {
                sign = 1;
            } else if(number[i] >= '0' && number[i] <= '9') {
                res = (res * 10) + (number[i] - '0');
            } else if(res) {
                res *= sign;
                ans += res;
                res = 0, sign = 1;
            }
        }
    }
    
    printf("%lld\n", ans);
    return 0;   
}
