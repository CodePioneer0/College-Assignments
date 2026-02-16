#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
//P1 -> Semaphore 0 
//P2 Section 1 -> Semaphore 1
//P3 -> Semaphore 2
//P2 Section 2 -> Semaphore 3

#define Key 123

#define P(sid) semop(sid, &Pop, 1);
#define V(sid) semop(sid, &Vop, 1);

int main(){
    int semid = semget(Key, 4, IPC_CREAT | 0777);

    semctl(semid, 0, SETVAL, 1);
    semctl(semid, 1, SETVAL, 0);
    semctl(semid, 2, SETVAL, 0);
    semctl(semid, 3, SETVAL, 0);

    struct sembuf Pop;
    Pop.sem_num = 0;
    Pop.sem_op = -1;
    Pop.sem_flg = 0;
    struct sembuf Vop;
    Vop.sem_num = 1;
    Vop.sem_op = 1;
    Vop.sem_flg = 0;

    while(1){
        P(semid);
        printf("I am P1\n");
        sleep(5);
        V(semid);
    }
}