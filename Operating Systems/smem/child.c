#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

struct shstruct{
    int flag;
    int n;
};

int facto(int n){
    if(n==0) return 1;
    int fact = 1;
    for(int i=2;i<=n;i++){
        fact = fact*i;
    }
    return fact;
}

int main(int argc,char*argv[]){
    if(argc<2){
        fprintf(stderr,"Usage : %s <number>\n",argv[0]);
        exit(1);
    }

    int shmid = atoi(argv[1]);
    struct shstruct *pi_child;

    pi_child = shmat(shmid, NULL, 0);
    if (pi_child == (void *)-1) { /* shmat fails */
        perror("shmat() failed at child: ");
        exit (1);
    }
    while(1){
        printf("Child Reads n : %d and flag : %d.\n", pi_child->n, pi_child->flag);
        if (pi_child->flag == 1) {
            pi_child->flag = 0;
            pi_child->n = facto(pi_child->n);
        }
        printf("Child writes n : %d and flag : %d.\n", pi_child->n, pi_child->flag);
        getchar();
    }
    shmdt(pi_child);
    exit(0);
}