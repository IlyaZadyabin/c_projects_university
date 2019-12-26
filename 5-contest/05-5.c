#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/limits.h>

unsigned long long hash_function(unsigned long long);

int main(int argc, char **argv) 
{
    char *file_path = argv[1];
    char *end;
    unsigned long long h_null = strtoull(argv[2], &end, 16);
    unsigned long long count = strtoull(argv[3], &end, 10);

    int fd = open(file_path, O_WRONLY | O_CREAT, 0660);
    if(fd < 0) {
        return 0;
    }

    lseek(fd, (count - 1) * sizeof(h_null), SEEK_END);

    for(count = count; count > 0; count--) {
        write(fd, &h_null, sizeof(h_null));
        lseek(fd, (-2ULL) * sizeof(h_null), SEEK_CUR);
        h_null = hash_function(h_null);
    }

    close(fd);
    return 0;
}
