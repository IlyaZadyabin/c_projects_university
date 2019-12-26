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

int
main(int argc, char **argv)
{
    struct Mesgbuffer { 
        long mesg_type; 
        long long value1;
        long long value2;
    };

    struct Mesgbuffer message;
    int error = 0;
    int key = strtol(argv[1], NULL, BASE);
    unsigned long long n = strtoull(argv[2], NULL, BASE);
    long long value1 = strtoll(argv[3], NULL, BASE);
    long long value2 = strtoll(argv[4], NULL, BASE);
    long long maxval = strtoll(argv[5], NULL, BASE);
    long long value3 = 0;
    
    int queue_id = msgget(key, 0666 | IPC_CREAT);

    int i, pid;
    int *pid_mas = calloc(n, sizeof(n));
    memset(pid_mas, 0, n);

    for(i = 0; i < n; i++) {
        pid = fork();
        if(pid < 0) {
            error = 1;
            break;
        }

        if(pid == 0) {
            while(msgrcv(queue_id, &message, sizeof(message), i + 1, 0) > 0) {
                value1 = message.value1;
                value2 = message.value2; 
                value3 = value1 + value2;
                
                printf("%d %lld\n", i, value3);
                fflush(stdout);

                if(value3 > maxval) {
                    break;
                }

                message.mesg_type = value3 % n + 1;
                message.value1 = value2;
                message.value2 = value3;
                
                msgsnd(queue_id, &message, sizeof(message), 0);
            }
            msgctl(queue_id, IPC_RMID, NULL);
            exit(0);
        }
        pid_mas[i] = pid;
    }

    if(error) {
        msgctl(queue_id, IPC_RMID, NULL);
        while (wait(NULL) > 0);
        exit(1);
    }

    message.mesg_type = 1;
    message.value1 = value1;
    message.value2 = value2;  
    msgsnd(queue_id, &message, sizeof(message), 0);

    while (wait(NULL) > 0);
    msgctl(queue_id, IPC_RMID, NULL);
    exit(0);
}
