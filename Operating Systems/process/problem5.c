#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    FILE *f = fopen("file.txt", "w");
    pid_t p;
    p = fork();
    if(p==0){
       char ch = 'A';
       fputc(ch, f);
       fclose(f);
       exit(0);
    }
    else{
        char ch = 'B';
        fputc(ch, f);
        fclose(f);
    }
    // char ch = 'A';
    // fputc(ch, f);
    // fclose(f);
    return 0;
}