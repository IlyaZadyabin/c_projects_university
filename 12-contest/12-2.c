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

volatile sig_atomic_t flag = 0;

void handler(int signal)
{
    if(signal == SIGINT) {
        flag = 0;
    } else if(signal == SIGQUIT) {
        flag = 1;
    }
}

int
main(void)
{
    int pid = getpid();
    int num = 0, sum = 0;
    struct sigaction act;

    memset(&act, 0, sizeof(act));
    act.sa_handler = handler;
    act.sa_flags = SA_RESTART;
    
    sigaction(SIGQUIT, &act, NULL);
    sigaction(SIGINT, &act, NULL);

    printf("%d\n", pid);
    fflush(stdout);

    while(scanf("%d", &num) != EOF) {
        if(flag == 0) {
            __builtin_sadd_overflow(sum, num, &sum);
        } else if(flag == 1) {
            __builtin_smul_overflow(sum, num, &sum);
        }
        printf("%d\n", sum);
        fflush(stdout);
    }
    return 0;
}
