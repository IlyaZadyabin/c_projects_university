#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <linux/limits.h>

enum { MAS_SIZE = 10 };

void
print_mas(unsigned long long *mas) 
{
    for(int i = 0; i < MAS_SIZE; i++) {
        printf("%d %llu\n", i, mas[i]);
    }
}

int
main(void)
{
    int c = 0;
    unsigned long long mas[MAS_SIZE];
    memset(mas, 0, MAS_SIZE * sizeof(unsigned long long));
    size_t path_size = PATH_MAX;

    char *path = calloc(PATH_MAX, sizeof(*path));
    if(path == NULL) {
        return -1;
    }

    size_t byte_read = getline(&path, &path_size, stdin);
    if(byte_read <= 0) {
        print_mas(mas);
    }

    int size = strlen(path);
    
    if(size >= 2) {
        if(path[size - 2] == '\r') {
            path[size - 2] = '\0';
        }
    }

    if(size >= 1) {
        if(path[size - 1] == '\n') {
            path[size -1 ] = '\0';
        }
    }

    FILE* fp = fopen(path, "r");
    if(fp == NULL) {
        print_mas(mas);
        return 0;
    }

    while((c = getc_unlocked(fp)) != EOF) {
        if(c >= '0' && c <= '9') {
            mas[c - '0']++;
        }
    }
    print_mas(mas);
    return 0;
}
