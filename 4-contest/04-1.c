#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

enum { SIZE = 10 };

char 
*getline2(FILE *f)
{
    int i = 0, capacity = SIZE;
    char *new_buf;
    char *buf = calloc(capacity, sizeof(*buf));
    if(buf == NULL) {
        return NULL;
    }
    int c;

    while((c = fgetc(f)) != EOF) {
        buf[i] = c;
        if(c == '\n') {
            i++;
            break;
        }

        if((i + 1) >= capacity) {
            capacity += SIZE;
            new_buf = realloc(buf, capacity * sizeof(*buf));

            if(new_buf == NULL) {
                free(buf);
                return NULL;
            } else {
                buf = new_buf;
            }
        }
        i++;
    }

    if(i == 0) {
        free(buf);
        return NULL;
    }
    buf[i] = '\0';
    return buf;
} 
