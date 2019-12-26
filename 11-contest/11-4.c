#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <linux/limits.h>
#include <limits.h>

void son_termination(int *pid_arr, int argc)
{
    int i = 0;
    if(pid_arr == NULL) {
        _exit(1);
    }

    for(i = 0; pid_arr[i] > 0; i++) {
        kill(pid_arr[i], SIGKILL);
    }

    while (wait(NULL) > 0);
    _exit(1);
}

void read_close(int fd) {
    if(fd != 0) {
        if(close(fd) < 0) {
            _exit(1);
        }
    }
}

void write_close(int fd) {
    if(fd != 1) {
        if(close(fd) < 0) {
            _exit(1);
        }
    }
}

int main(int argc, char **argv)
{
    int pid, i = 0, fd_old[2], fd_new[2];
    fd_old[0] = 0; fd_old[1] = 1;
    fd_new[0] = 0; fd_new[1] = 1;

    int *pid_arr = calloc(argc, sizeof(*pid_arr));
    if(pid_arr == NULL) {
        son_termination(pid_arr, argc);
    }
    memset(pid_arr, 0, argc * sizeof(*pid_arr));

    for(i = 1; i < argc; i++) {
        if(pipe(fd_new) < 0) {
            son_termination(pid_arr, argc);
        }

        if(i == (argc - 1)) {
            fd_new[1] = 1;
        }

        if((pid = fork()) < 0) {
            son_termination(pid_arr, argc);
        }

        if(pid > 0) {
            pid_arr[i - 1] = pid;
        }

        if(pid == 0) {
            write_close(fd_old[1]); read_close(fd_new[0]);
            if(dup2(fd_old[0], 0) < 0) {
                _exit(1);
            }
            read_close(fd_old[0]);

            if(dup2(fd_new[1], 1) < 0) {
                _exit(1);
            }
            write_close(fd_new[1]);

            execlp(argv[i], argv[i], NULL);
            _exit(1);
        }   
        read_close(fd_old[0]);
        write_close(fd_old[1]); 
        write_close(fd_new[1]);

        fd_old[0] = fd_new[0];
    }

    read_close(fd_new[0]);
    
    while (wait(NULL) > 0);
    return 0;
}
