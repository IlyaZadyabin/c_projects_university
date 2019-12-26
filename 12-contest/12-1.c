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

void
handler_funtion(int signal)
{
    if(flag == 5) {
        exit(0);
    }

    printf("%d\n", flag);
    fflush(stdout);
    flag++;
}

int
main(void)
{
    int pid = getpid();
    struct sigaction act;

    memset(&act, 0, sizeof(act));
    act.sa_handler = handler_funtion;
    act.sa_flags = SA_RESTART;
    
    sigaction(SIGHUP, &act, NULL);

    printf("%d\n", pid);
    fflush(stdout);

    while(1) {
        pause();
    }
    return 0;
}
