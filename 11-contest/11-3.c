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

int main(int argc, char **argv)
{    
    int fd[2], son, status, pid;
    if(pipe(fd) < 0) {
        _exit(1);
    }

    if((son = fork()) == 0) {
        close(fd[0]);
        if((pid = fork()) < 0) {
            exit(1);
        }

        if(pid == 0) {
            int file1 = open(argv[4], O_RDONLY, 0666); dup2(file1, 0); close(file1);
            dup2(fd[1], 1); close(fd[1]); 
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        }
        waitpid(pid, &status, 0);

        if(WIFEXITED(status) && (WEXITSTATUS(status) == 0)) {
            if((pid = fork()) < 0) {
                exit(1);
            }
            if(pid == 0) {
                dup2(fd[1], 1); close(fd[1]);
                execlp(argv[2], argv[2], NULL);
                _exit(1);
            }
            waitpid(pid, &status, 0);
        }
        exit(0);
    }

    if ((son = fork()) == 0) {
        close(fd[1]);
        int file2 = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0666);
        dup2(file2, 1); close(file2);
        dup2(fd[0], 0); close(fd[0]); 
        
        execlp(argv[3], argv[3], NULL);
        _exit(1);
    }

    close(fd[0]); close(fd[1]);
    wait(NULL); wait(NULL);
    return 0;
}
