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

enum { BASE = 10, ARRAY_SHIFT = 1 };

void child(int semaphore_id, int shared_mem_id, unsigned long long *mem_ptr, int nproc,
        int my_sem, unsigned long long maxval) {

    struct sembuf sem_mas[1];
    sem_mas[0].sem_num = my_sem;      
    sem_mas[0].sem_op = -1;
    sem_mas[0].sem_flg = 0;

    while(semop(semaphore_id, sem_mas, 1) >= 0) {
        printf("%d %llu %llu\n", my_sem + ARRAY_SHIFT, mem_ptr[0], mem_ptr[1] + ARRAY_SHIFT);
        fflush(stdout);
        mem_ptr[0] += 1;
        mem_ptr[1] = my_sem;

        if (mem_ptr[0] > maxval) {
            break;
        }

        unsigned long long num = mem_ptr[0] % nproc;
        struct sembuf mas[1];
        mas[0].sem_num = (num * num * num * num) % nproc;      
        mas[0].sem_op = 1;
        mas[0].sem_flg = 0;
        
        semop(semaphore_id, mas, 1);
    }
    
    shmctl(shared_mem_id, IPC_RMID, NULL);
    semctl(semaphore_id, 0, IPC_RMID);
    exit(0);
}

int main(int argc, char **argv) {
    int i = 0;
    int num_of_proc = strtol(argv[1], NULL, BASE);
    int key = strtol(argv[2], NULL, BASE);
    unsigned long long int maxval = strtoull(argv[3], NULL, BASE);

    int semaphore_id = semget(key, num_of_proc, 0666 | IPC_CREAT);
    unsigned long long int *mem_ptr;
    int shared_mem_id = shmget(key, sizeof(*mem_ptr) * 2, 0666 | IPC_CREAT);
    mem_ptr = shmat(shared_mem_id, NULL, 0);
    mem_ptr[0] = 0;
    mem_ptr[1] = -ARRAY_SHIFT;

    for(i = 0; i < num_of_proc; i++) {
        if (fork() == 0) {
            child(semaphore_id, shared_mem_id, mem_ptr, num_of_proc, i, maxval);
        }
    }

    struct sembuf mas[1];
    mas[0].sem_num = 0;
    mas[0].sem_op = 1;
    mas[0].sem_flg = 0;
    semop(semaphore_id, mas, 1);

    while (wait(NULL) > 0);
    return 0;
}
