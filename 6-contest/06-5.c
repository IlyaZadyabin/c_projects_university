#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>

enum { INPUT_SIZE = 1000, YEAR_REF_POINT = 1900 };

int main(int argc, char **argv)
{
    struct tm shift;
    int prev_shift = 0, cur_shift = 0, i;

    char input_string[INPUT_SIZE];
    FILE *f = fopen(argv[1], "r");
    if(f == NULL) {
        exit(1);
    }
    
    char *tmp_str = input_string;
    size_t size = INPUT_SIZE;

    for(i = 0; getline(&tmp_str, &size, f) > 0; i++) {
        sscanf(tmp_str, "%d/%d/%d%d:%d:%d", &shift.tm_year, &shift.tm_mon, &shift.tm_mday,
            &shift.tm_hour, &shift.tm_min, &shift.tm_sec);
        shift.tm_year -= YEAR_REF_POINT;
        shift.tm_mon -= 1;
        shift.tm_isdst = -1;

        if(i == 0) {
            prev_shift = mktime(&shift);
        } else {
            cur_shift = mktime(&shift);
            printf("%d\n", cur_shift - prev_shift);
            prev_shift = cur_shift;
        }
    }
    
    fclose(f);
    return 0;
}
