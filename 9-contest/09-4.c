#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i, N;
    scanf("%d", &N);

    for(i = 1; i <= N; i++)
    {
        int pid = fork();

        if(pid > 0) {
            if(i == N) {
                printf("%d\n", i);
            } else {
                printf("%d ", i);
            }

            fflush(stdout);
            wait(NULL);
            exit(0);
        }
    }
}
