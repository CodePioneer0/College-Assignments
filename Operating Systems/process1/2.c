#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc ,char *argv[]){
    if(argc<2){
        printf("Please provide a string to reverse\n");
        return 1;
    }
    pid_t p;
    for(int i=1;i<argc;i++){
        p = fork();
        if(p==-1){
            perror("Fork Failed");
            exit(1);
        }
        if(p==0){
            execl("./reverse","reverse",argv[i],NULL);
            perror("Exec Failed");
            exit(1);
        }
        else{
            printf("Child Process id : %d\n",p);
            wait(NULL);
        }
    }
    return 0;
}
