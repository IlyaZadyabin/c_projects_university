#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int pid_son = fork();

    if(pid_son == 0) {
        int pid_grandson = fork();

        if(pid_grandson == 0) {
            wait(NULL);
            printf("3 ");
        } else {
            wait(NULL);
            printf("2 ");
        }
    } else {
        wait(NULL);
        printf("1\n");
    }
}
