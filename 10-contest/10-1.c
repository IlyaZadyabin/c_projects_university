#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int
main(int argc, char **argv)
{
    int pid, status, read_fd, write_fd, error_fd;
    if((pid = fork()) < 0) {
        _exit(0);
    }

    if (pid == 0) {
        if((read_fd = open(argv[2], O_RDONLY, 0)) < 0) {
            _exit(42);
        }

        if(dup2(read_fd, 0) < 0) {
            _exit(42);
        }
        close(read_fd);

        if((write_fd = open(argv[3], O_WRONLY | O_CREAT | O_APPEND, 0660)) < 0) {
            _exit(42);
        }

        if(dup2(write_fd, 1) < 0) {
            _exit(42);
        }
        close(write_fd);

        if((error_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0660)) < 0) {
            _exit(42);
        }

        if(dup2(error_fd, 2) < 0) {
            _exit(42);
        }
        close(error_fd); 
        
        execlp(argv[1], argv[1], NULL);
        _exit(42);
    }
    waitpid(pid, &status, 0);
    printf("%d\n", status);
    return 0;
}

