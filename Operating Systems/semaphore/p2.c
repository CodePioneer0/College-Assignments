#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
//P1 -> Semaphore 0 
//P2 Section 1 -> Semaphore 1
//P3 -> Semaphore 2
//P2 Section 2 -> Semaphore 3

#define Key 123

int main(){
    int semid = semget(Key, 4, IPC_CREAT | 0777);

    struct sembuf Pop1;
    struct sembuf Vop1;
    Pop1.sem_num = 1;
    Pop1.sem_op = -1;
    Pop1.sem_flg = 0;

    Vop1.sem_num = 2;
    Vop1.sem_op = 1;
    Vop1.sem_flg = 0;
    
    struct sembuf Pop2;
    struct sembuf Vop2;
    Pop2.sem_num = 3;
    Pop2.sem_op = -1;
    Pop2.sem_flg = 0;
    Vop2.sem_num = 0;
    Vop2.sem_op = 1;
    Vop2.sem_flg = 0;
    
    while(1){
        semop(semid, &Pop1, 1);
        printf("I am P2 section 1\n");
        sleep(5);
        semop(semid, &Vop1, 1);

        semop(semid, &Pop2, 1);
        printf("I am P2 section 2\n");
        sleep(5);
        semop(semid, &Vop2, 1);
    }
}