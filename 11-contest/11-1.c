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
    status = pipe(fd);
    if (status == -1) { 
        printf("%s\n", strerror(errno));
        exit(1);
    }

    time_t rawtime;
    struct tm *timeinfo;

    int pid_son = fork();

    if(pid_son == 0) { 
        int pid_grandson = fork();
        if(pid_grandson == 0) {
            close(fd[0]); 
            rawtime = time(NULL);
            timeinfo = localtime (&rawtime);
            write(fd[1], &rawtime, sizeof(rawtime)); 
            write(fd[1], &rawtime, sizeof(rawtime)); 
            
            printf("D:%.2d\n", timeinfo->tm_mday);
            close(fd[1]); 
            exit(0);
        }

        if(pid_grandson > 0) {
            close(fd[1]);
            waitpid(pid_grandson, NULL, 0);
            read(fd[0], &rawtime, sizeof(timeinfo));
            timeinfo = localtime (&rawtime);     

            printf("M:%.2d\n", timeinfo->tm_mon + 1);
            close(fd[0]);
            exit(0);
        }
    }

    if(pid_son > 0) {
        close(fd[1]);
        waitpid(pid_son, NULL, 0);
        
        read(fd[0], &rawtime, sizeof(timeinfo));
        timeinfo = localtime (&rawtime);

        printf("Y:%.4d\n", timeinfo->tm_year + 1900);
        close(fd[0]);
        exit(0);
    }
}
