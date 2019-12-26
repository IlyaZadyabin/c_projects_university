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
#include <linux/limits.h>

enum { BASE = 10 };

int main(int argc, char **argv)
{
    sigset_t mask;
    
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    int i, pid, cnt = 0, status;
    FILE *file;
    char cmd[PATH_MAX];
    int N = strtol(argv[1], NULL, BASE);

    for(i = 2; i <= N + 1 && i < argc; i++) {
        pid = fork();
        if(pid < 0) {
            _exit(1);
        }
        
        if(pid == 0) {
            file = fopen(argv[i], "r");
            fscanf(file, "%s", cmd);
            execl(cmd, cmd, NULL);
            _exit(1);
        }
    }

    while((pid = wait(&status)) > 0) {
        if(WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            cnt++;
        }
    }

    for(i = N + 2; i < argc; i++) {
        pid = fork();
        if(pid < 0) {
            _exit(1);
        }

        if (pid == 0) {
            file = fopen(argv[i], "r");
            fscanf(file, "%s", cmd);
            execl(cmd, cmd, NULL);
            _exit(1);
        } else if((pid = wait(&status)) > 0) {
            if(WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                cnt++;
            }
        }
    }

    printf("%d\n", cnt);
    fflush(stdout);
    return 0;
}
