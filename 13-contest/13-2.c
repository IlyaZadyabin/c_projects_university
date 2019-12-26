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

void
child(int semaphore_id, int shared_mem_id, int *mem_ptr, unsigned long long nproc,
        unsigned seed, unsigned long long count, unsigned long long iter_count) {
    srand(seed);
    int i, ind1, ind2, value;

    for(i = 0; i < iter_count; i++) {
        ind1 = rand() % count;
        ind2 = rand() % count;
        value = rand() % BASE;

        if(ind1 == ind2) {
            continue;
        }
        semop(semaphore_id, (struct sembuf[]) {{count, -1, 0}}, 1);

        semop(semaphore_id, (struct sembuf[]) {{ind1, -1, 0}}, 1);
        semop(semaphore_id, (struct sembuf[]) {{ind2, -1, 0}}, 1);

        semop(semaphore_id, (struct sembuf[]) {{count, 1, 0}}, 1);

        operation(mem_ptr, ind1, ind2, value);

        semop(semaphore_id, (struct sembuf[]) {{ind1, 1, 0}}, 1);        
        semop(semaphore_id, (struct sembuf[]) {{ind2, 1, 0}}, 1);        
    }
    exit(0);
}

int
main(int argc, char **argv)
{
    unsigned long long count = strtoull(argv[1], NULL, BASE);
    int key = strtol(argv[2], NULL, BASE);
    unsigned long long nproc = strtoull(argv[3], NULL, BASE);
    unsigned long long iter_count = strtoull(argv[4], NULL, BASE);

    int semaphore_id = semget(key, count + 1, 0666 | IPC_CREAT);
    int shared_mem_id = shmget(key, sizeof(int) * count, 0666 | IPC_CREAT);
    int *mem_ptr = shmat(shared_mem_id, NULL, 0);

    int i, num;
    for(i = 0; i < count; i++) {
        semop(semaphore_id, (struct sembuf[]) {{i, 1, 0}}, 1);
        scanf("%d", &num);
        mem_ptr[i] = num;
    }
    semop(semaphore_id, (struct sembuf[]) {{count, 1, 0}}, 1);

    unsigned seed = 0;
    for(i = 0; i < nproc; i++) {
        if (fork() == 0) {
            seed = strtoul(argv[i + 5], NULL, BASE);
            child(semaphore_id, shared_mem_id, mem_ptr, nproc, seed, count, iter_count);
        }
    }

    while (wait(NULL) > 0);
    for(i = 0; i < count; i++) {
        printf("%d\n", mem_ptr[i]);
        fflush(stdout);
    }

    shmctl(shared_mem_id, IPC_RMID, NULL);
    semctl(semaphore_id, 0, IPC_RMID);
    return 0;
}
