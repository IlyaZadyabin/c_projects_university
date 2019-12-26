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

enum { STRUCT_SIZE = 12 };

void
rec_access(int fd, int idx)
{
    int ans, new_idx, size = STRUCT_SIZE;
    lseek(fd, idx * size, SEEK_SET);
    read(fd, &ans, sizeof(ans));

    lseek(fd, idx * size + 2 * sizeof(idx), SEEK_SET);
    read(fd, &new_idx, sizeof(new_idx));
    if(new_idx != 0) {
        rec_access(fd, new_idx);
    }

    printf("%d\n", ans);

    lseek(fd, idx * size + sizeof(idx), SEEK_SET);
    read(fd, &new_idx, sizeof(new_idx));
    if(new_idx != 0) {
        rec_access(fd, new_idx);
    }
}

int
main(int argc, char **argv) 
{
    int idx;
    char file_path[PATH_MAX];

    snprintf(file_path, PATH_MAX, "%s", argv[1]);
    int fd = open(file_path, O_RDONLY);
    if(fd < 0) {
        return 0;
    }

    if(read(fd, &idx, sizeof(idx)) > 0) {
        rec_access(fd, 0);
    }

    close(fd);
    return 0;
}
