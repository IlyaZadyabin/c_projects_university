#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <time.h>

int main(void){
    int fd[2];
    int status;
    int num_print = 0;
    int num_scan = 0;
    long long int ans = 0;
    status = pipe(fd);
    if (status == -1) { 
        printf("%s\n", strerror(errno));
        exit(1);
    }

    int pid_son = fork();

    if(pid_son == 0) { 
        int pid_grandson = fork();
        if(pid_grandson == 0) {
            close(fd[1]); 
            while(read(fd[0], &num_scan, sizeof(num_scan)) > 0) {
                ans += num_scan;
            }

            printf("%lld\n", ans);
            close(fd[0]); 
            exit(0);
        }

        if(pid_grandson > 0) {
            close(fd[1]), close(fd[0]);
            exit(0);
        }
    }

    if(pid_son > 0) {
        close(fd[0]);
        while(scanf("%d", &num_print) != EOF) {
            write(fd[1], &num_print, sizeof(num_print));
        }

        waitpid(pid_son, NULL, 0);
        close(fd[1]);
        exit(0);
    }
}
