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

int
parse_rwx_permissions(const char *str) 
{
    if(str == NULL) {
        return -1;
    }
    const char example[] = "rwxrwxrwx";
    int ans = 0;
    unsigned int bit = 0;

    size_t size = sizeof(example) - 1;
    if(strlen(str) != size) {
        return -1;
    }
    
    for(int i = 0; i < size; i++) {
        if(str[i] == example[i] || str[i] == '-') {
            if(str[i] == '-') {
                bit = 0; 
            } else {
                bit = 1;
            }

            if(i) {
                ans <<= 1;
            }
            ans += bit;

        } else {
            return -1;
        }
    }
    return ans;
}
