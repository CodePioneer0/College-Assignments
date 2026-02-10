#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    FILE *f = fopen("file.txt", "r");
    pid_t p;
    p = fork();
    if(p==0){
       char ch = fgetc(f);
       printf("%c\n", ch);
       fclose(f);
       exit(0);
    }
    else{
        char ch = fgetc(f);
        printf("%c\n", ch);
        fclose(f);
    }
    return 0;
}
