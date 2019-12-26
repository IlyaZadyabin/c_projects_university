#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int num, status;
    int first_pid = fork();

    if(first_pid == 0) {
        setbuf(stdin, NULL);
        while(scanf("%d", &num) != EOF)
        {
            int pid = fork();
            if(pid == -1) {
                exit(1);
            }

            if(pid > 0) {    
                waitpid(pid, &status, WUNTRACED);
                if (WIFEXITED(status) == 1 && WEXITSTATUS(status) == 1) {
                    exit(1);
                }
                printf("%d\n", num);
                exit(0);
            }
            setbuf(stdin, NULL); 
        }
    } else {
        waitpid(first_pid, &status, WUNTRACED);
        if (WIFEXITED(status) == 1 && WEXITSTATUS(status) == 1) {
            printf("-1\n");
        }
    }
    return 0;
}
