#include <stdio.h>

int
main(void)
{
    int cur_size = 0, flag = 0, max_size = 0, c = 0;
    c = getchar();

    while (c != EOF) {    
        if (c == 'q') {
            flag = 1;
        }

        if (c >= 'a' && c <= 'z') {
            cur_size++;
        } else {
            if (flag == 0 && cur_size > max_size) {
                max_size = cur_size;
            }
            
            cur_size = 0, flag = 0;
        }
        c = getchar();
    }

    if (c == EOF && flag == 0 && cur_size > max_size) {
        max_size = cur_size;
    }

    printf("%d\n", max_size);
}
