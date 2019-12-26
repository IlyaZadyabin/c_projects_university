#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    DIR *directory = opendir(argv[1]);
    if(directory == NULL) {
        return 0;
    }

    struct dirent *dir;
    unsigned long long whole_size = 0;
    while((dir = readdir(directory)) != NULL) {

        char path[PATH_MAX];
        if(snprintf(path, sizeof(path),"%s/%s",argv[1],dir->d_name) >= sizeof(path)) {
            exit(1);
        }

        struct stat st;
        if(stat(path, &st) >= 0 && S_ISREG(st.st_mode) && st.st_uid == getuid()
                && (*(dir->d_name) >= 'A' && *(dir->d_name) <= 'Z')) {
            whole_size += st.st_size;
        }
    }

    closedir(directory);
    printf("%llu\n", whole_size);
    return 0;
}
