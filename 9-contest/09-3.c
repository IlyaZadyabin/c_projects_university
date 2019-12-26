#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

enum { BUF_SIZE = 8, BASE = 10, NUM_OF_SONS = 3 };

int
main(void)
{
    char buf[BUF_SIZE];
    char *buf_ptr = buf;
    int i;

    for(i = 1; i <= NUM_OF_SONS; i++)
    {
        long num;
        int pid = fork();

        if(pid == 0) {
            read(0, buf_ptr, BUF_SIZE);
            num = strtol(buf_ptr, NULL, BASE);
            printf("%d %ld\n", i, num * num);
            exit(0);
        }
    }

    for(i = 0; i < NUM_OF_SONS; i++){
        wait(NULL);
    }
}

