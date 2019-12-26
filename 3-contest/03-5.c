#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

enum { SIZE = 1024, FLAG_SIZE = 15, EMPTY = 1, NOT_EMPTY = 2, CHARACTER = 3, NUMBERS = 4 };

char 
*getline2(FILE *f);

int
main(void)
{
    char *end, *str = 0, *tmp_str = 0;
    int num_amount = 0, i, j, sum = 0, flag = EMPTY;
    int x;

    for(j = 1; (str = getline2(stdin)) != NULL; j++) {
        flag = NOT_EMPTY;
        tmp_str = str;
        sum = 0;
        for(i = 1; *tmp_str != 0; i ++) {
            x = strtol(tmp_str, &end, 10);

            if(tmp_str == end) {
                if(isspace((unsigned char) *tmp_str) == 0) {
                    flag = CHARACTER;
                    break;
                }
                tmp_str++;
                continue;
            } else {
                flag = NUMBERS;
                if(errno == ERANGE) {
                    if(x < 0) {
                        x = -i;
                    } else {
                        x = i;
                    }
                    errno = 0;
                }
                __builtin_add_overflow(sum, x, &sum);
                tmp_str = end;
            }
        }
        if(flag == CHARACTER) {
            printf("%d\n", 0xbedabeda + j);
        } else if(flag == NUMBERS) {
            printf("%d\n", sum);
        } else {
            printf("%d\n", 0x0bad1dea + j);
        }
        num_amount++;
        free(str);
    }
    return 0;
}
