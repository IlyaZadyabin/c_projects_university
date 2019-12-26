#include <stdio.h>
#include <stdint.h>
#include <linux/limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>

int
main(int argc, char **argv)
{
    long long num, min = LLONG_MAX, i = 0, min_idx = 0;
    char *file_path = argv[1];

    int f = open(file_path, O_RDWR);
    if(f < 0) {
        return 0;
    }

    while(read(f, &num, sizeof(num)) == sizeof(num)) {
        if(num < min) {
            min_idx = i;
            min = num;
        } 
        i++;
    }

    if(i == 0) {
        close(f);
        return 0;
    }

    if(lseek(f, min_idx * sizeof(min), SEEK_SET) < 0) {
        return 0;
    }

    min = -(unsigned long long) min;
    if(write(f, &min, sizeof(min)) != sizeof(min)) {
        return 0;
    }

    close(f);
    return 0;
}
