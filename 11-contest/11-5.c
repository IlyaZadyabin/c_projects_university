#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

enum { BASE = 10, PID1 = 1, PID2 = 2 }; 

void
proc(int rfd, int wfd, int id, long long unsigned int max_num)
{
    FILE *read_stream = fdopen(rfd, "r");
    FILE *write_stream = fdopen(wfd, "w");
    long long unsigned int num = 0;

    while (1) {
        if(max_num == 1) {
            break;
        }

        if(max_num == 2) {
            if(id == 1) {
                printf("%d %llu\n", id, max_num - 1);
            } 
            break;
        }     

        if(fscanf(read_stream, "%llu", &num) < 0) {
            break;
        }

        printf("%d %llu\n", id, num);
        fflush(stdout);

        num += 1;
        if(num >= max_num) {
            break;
        }

        fprintf(write_stream, "%llu\n", num);
        fflush(write_stream);

        if(num >= max_num - 1) {
            close(wfd); close(rfd);
        }
    }
}


int
main(int argc, char **argv)
{
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);

    long long unsigned max_number = strtoull(argv[1], NULL, BASE);    
    long long unsigned int x = 1;

    FILE *write_stream = fdopen(fd1[1], "w");
    fprintf(write_stream, "%llu\n", x);
    fflush(write_stream);
    
    int pid1 = fork();
    if (pid1 == 0) {
        proc(fd1[0], fd2[1], PID1, max_number);
        exit(0);
    }

    int pid2 = fork();
    if (pid2 == 0) {
        proc(fd2[0], fd1[1], PID2, max_number);
        exit(0);
    }

    wait(NULL); wait(NULL);
    close(fd1[1]); close(fd2[1]);
    close(fd1[0]); close(fd2[0]);
    printf("Done\n");
    fflush(stdout);
    return 0;
}
