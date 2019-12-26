#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char **argv)
{
    int fd = open(argv[1], O_RDONLY);
    if(fd < 0) {
        exit(1);
    }

    int flag = 0;
    unsigned short min = USHRT_MAX, higher_byte = 0, lower_byte = 0, res = 0;
    
    while(read(fd, &higher_byte, 1) > 0 && read(fd, &lower_byte, 1) > 0) {
        res = (higher_byte << CHAR_BIT);
        res += lower_byte;

        if(res % 2 == 0 && res <= min) {
            flag = 1;
            min = res;
        }
    }

    if(flag) {
        printf("%hu\n", min);
    }
    close(fd);
    return 0;
}
