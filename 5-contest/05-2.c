#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

enum { SHORT_SIZE = 2 };

int main(int argc, char **argv) 
{
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0600);
    
    unsigned short input = 0;
    unsigned char ans[SHORT_SIZE];
    
    while(scanf("%6hu", &input) > 0) {
        ans[0] = (input >> CHAR_BIT);
        ans[1] = input;
        write(fd, ans, SHORT_SIZE);
    }

    close(fd);
    return 0;
}
