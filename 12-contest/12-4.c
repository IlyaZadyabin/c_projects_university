#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

enum { BASE = 10, FIRST_PROC = 1, SECOND_PROC = 2 };

void
sig_handler(int sig)
{
    signal(sig, sig_handler);
}

void child(int *fd, int proc_order, unsigned long long max_num)
{
    int sender_pid;
    unsigned long long num = 0;
    FILE *read_stream = fdopen(fd[0], "r");
    FILE *write_stream = fdopen(fd[1], "w");
    
    fprintf(write_stream, "%d\n", getpid());
    fflush(write_stream);

    while(1) {
        pause();
        fscanf(read_stream, "%d %llu", &sender_pid, &num);

        if(num >= max_num) {
            fclose(read_stream); fclose(write_stream);
            exit(0);
        }

        printf("%d %llu\n", proc_order, num);
        fflush(stdout);
        num += 1;

        fprintf(write_stream, "%d %llu\n", getpid(), num);
        fflush(write_stream);
        kill(sender_pid, SIGUSR1);
    }    
}

int 
main(int argc, char **argv)
{
    int fd[2], pid = 0;
    unsigned long long max_num = strtoull(argv[1], NULL, BASE);
    pipe(fd);

    signal(SIGUSR1, sig_handler);

    int pid1 = fork();
    if (pid1 == 0) {
        child(fd, FIRST_PROC, max_num);
    }

    int pid2 = fork();
    if (pid2 == 0) {
        child(fd, SECOND_PROC, max_num);
    }

    FILE *read_stream = fdopen(fd[0], "r");
    if(fscanf(read_stream, "%d %d", &pid, &pid) > 0) {
        fclose(read_stream);
        FILE *write_stream = fdopen(fd[1], "w");

        unsigned long long int first_message = 1;
        fprintf(write_stream, "%d %llu\n", pid2, first_message);
        fflush(write_stream);
        kill(pid1, SIGUSR1);

        pid = wait(NULL); 
        pid = ((pid == pid1) ? pid2 : pid1); 

        fprintf(write_stream, "%d %llu\n", pid, max_num);
        fflush(write_stream);
        kill(pid, SIGUSR1);
        wait(NULL);

        fclose(write_stream);
        printf("Done\n");
        fflush(stdout);
        return 0;
    }
}
