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

    struct sembuf Pop;
    Pop.sem_num = 2;
    Pop.sem_op = -1;
    Pop.sem_flg = 0;
    struct sembuf Vop;
    Vop.sem_num = 3;
    Vop.sem_op = 1;
    Vop.sem_flg = 0;

    while(1){
        P(semid);
        printf("I am P3\n");
        sleep(5);
        V(semid);
    }
}