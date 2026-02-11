#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
void split_line(char *line, char **myargv) {
    int i=0;
    int in_word = 0;
    for(int k=0; line[k] != '\0'; k++){
        if(line[k] != ' '){
            if(!in_word){
                myargv[i] = &line[k];
                i++;
                in_word = 1;
            }
        }
        else{
            line[k] = '\0';
            in_word = 0;
        }
    }
    myargv[i] = NULL;
}
void remove_newline(char *line) {
    int len = strlen(line);
    if(len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
    }
}
int main(int argc ,char *argv[]){
    char line[100];
    char *myargv[100];
    while(1){
        printf("Enter Command : ");
        if(fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }
        remove_newline(line);
        split_line(line, myargv);
        if(myargv[0] == NULL) {
            continue;
        }
        pid_t p = fork();
        if(p == -1){
            perror("Fork Failed");
            exit(1);
        }
        if(p == 0){
            execvp(myargv[0], myargv);
            perror("Exec Failed");
            exit(1);
        }
        else{
            int cid;
            int plstatus;
            cid = wait(&plstatus);
            if(WIFEXITED(plstatus)){
                printf("Normal terminaltion\n");
            }
            else{
                printf("Abnormal termination\n");
            }
        }
    }
}