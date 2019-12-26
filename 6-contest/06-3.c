#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <linux/limits.h>

void 
normalize_path(char *buf)
{
    char *tmp_buf = buf, *tmp_ans = buf;
    
    while(*tmp_buf != 0) {
        if(*tmp_buf == '/') {
            *tmp_ans = *tmp_buf;
            tmp_ans++, tmp_buf++;

            while(*tmp_buf == '/') {
                tmp_buf++;
            }
        } else {
            *tmp_ans = *tmp_buf;
            tmp_ans++, tmp_buf++;
        }
    }
    *tmp_ans = 0;
}
