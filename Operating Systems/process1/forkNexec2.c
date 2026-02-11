#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(int agrc,char *argv[]){
	char s[100];
	while(1){
		printf("Enter the name of the exucutable file : ");
		scanf("%s",s);
		pid_t p;
		p = fork();
		if(p==0){
			printf("Child Printing String : %s\n",s);
			exit(0);
		}
		else{
			int cid;
			int plstatus;
			cid = wait(&plstatus);
		}
	}
}

