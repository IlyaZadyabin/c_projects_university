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
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>

enum { BASE = 10 };

int main(int argc, char **argv)
{
    int i, num = 0, remainder, pid;
    int count = strtol(argv[1], NULL, BASE);
    creat("key.txt", O_CREAT | O_RDONLY);
    int key = ftok("key.txt", 0);
    int semaphore_id = semget(key, count, 0666 | IPC_CREAT);

    setbuf(stdin, NULL);

    for(i = 0; i < count; i++) {
        semop(semaphore_id, (struct sembuf[]) {{i, 0, 0}}, 1);
    }

    for(i = 0; i < count; i++) {
        pid = fork();
        if(pid < 0) {
            semctl(semaphore_id, 0, IPC_RMID);
            while(wait(NULL) > 0);
            unlink("key.txt");
            exit(0);
        }

        if(pid == 0) {
            while(semop(semaphore_id, (struct sembuf[]) {{i, -1, 0}}, 1) == 0) {
                if(scanf("%d", &num) == EOF) {
                    break;
                }
                printf("%d %d\n", i, num);
                fflush(stdout);
                if(num < 0) {
                    if(num % count == 0 ) {
                        remainder = 0;
                    } else {
                        remainder = num % count + count;
                    }
                } else {
                    remainder = num % count;
                }
                semop(semaphore_id, (struct sembuf[]) {{remainder, 1, 0}}, 1);
            }
            semctl(semaphore_id, 0, IPC_RMID);
            exit(0);
        }
    }

    semop(semaphore_id, (struct sembuf[]) {{0, 1, 0}}, 1);
    while(wait(NULL) > 0);
    unlink("key.txt");
    semctl(semaphore_id, 0, IPC_RMID);
    exit(0);
}
