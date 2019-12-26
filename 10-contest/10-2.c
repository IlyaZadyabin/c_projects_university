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

int mysys(const char *str)
{
    int pid, status;

    if((pid = fork()) < 0) {
        _exit(-1);
    }

    if (pid == 0) {
        execlp("/bin/sh", "sh", "-c", str, NULL);        
        _exit(127);
    }

    waitpid(pid, &status, 0);
    if(WIFSIGNALED(status)) {
        return WTERMSIG(status) + 128;
    }
    
    if (WIFEXITED(status) && (WEXITSTATUS(status) >= 0) && (WEXITSTATUS(status) <= 127)) {
        return WEXITSTATUS(status);
    }
    return 0;
}
