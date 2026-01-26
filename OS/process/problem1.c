#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
void reverse(char *s){
	int n = strlen(s);
	for(int i=0;i<n/2;i++){
		char temp = s[i];
		s[i] = s[n-i-1];
		s[n-i-1] = temp;
	}
}


int main(int argc,char *argv[]){
	pid_t p;
	for(int i=1;i<argc;i++){
		p = fork();
		if(p!=0){
			printf("Child id : %d\n",p);
		}
		if(p==0){
			reverse(argv[i]);
			printf("The String %d is  %s\n",i,argv[i]);
			exit(0);
		}
	}
}
