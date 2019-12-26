#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

int
main(int argc, char **argv)
{
    char *path;
    int i;
    struct stat st;
    unsigned long long int whole_size = 0;

    for(i = 1; i < argc; i++) {
        path = argv[i];
        int fd = lstat(path, &st);
        if(fd == 0 && S_ISREG(st.st_mode) && st.st_nlink == 1) {
            whole_size += st.st_size;
        }
    }
    printf("%llu\n", whole_size);
    return 0;
}
