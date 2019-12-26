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
#include <math.h>

enum { BASE = 10 };

int
is_prime(long long int num)
{
    long long int i = 0;
    if(num < 0) {
        num = -num;
    }

    for (i = 2; i <= (long long int) (sqrt(num)) + 1; i++) { 
        if (num % i == 0) { 
            return 0; 
        } 
    } 
    return 1;
}

volatile sig_atomic_t flag = 0;
long long int cur_prime = 0;

void
handler_funtion(int sig)
{
    if(sig == SIGTERM) {
        exit(0);
    }

    if(flag == 3) {
        exit(0);
    }
    flag++;
    printf("%lld\n", cur_prime);
    fflush(stdout);
}

int
main(void)
{
    int pid = getpid();
    struct sigaction act;

    memset(&act, 0, sizeof(act));
    act.sa_handler = handler_funtion;
    act.sa_flags = SA_RESTART;
    
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGINT, &act, NULL);

    printf("%d\n", pid);
    fflush(stdout);

    long long int i = 0, low, high;
    scanf("%lld %lld", &low, &high);

    for(i = low; i < high; i++ ) {
        if(is_prime(i)) {
            cur_prime = i;
        }
    }
    printf("-1\n");
    fflush(stdout);
    return 0;
}
