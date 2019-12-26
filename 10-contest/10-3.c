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

int cmd_execution(char *cmd) 
{
    int pid, status;
    if((pid = fork()) < 0) {
        exit(1);
    }
    if(pid == 0) {
        execlp(cmd, cmd, NULL);
        _exit(1);
    }

    waitpid(pid, &status, 0);
    if(WIFEXITED(status) && (WEXITSTATUS(status) == 0)) {
        return 0;
    } else {
        return 1;
    }
}

int main(int argc, char **argv)
{   
    if(cmd_execution(argv[1]) == 0) {
        exit(cmd_execution(argv[3]));
    } else {
        if(cmd_execution(argv[2]) == 0) {
            exit(cmd_execution(argv[3]));
        } else {
            exit(1);
        }
    }
}
