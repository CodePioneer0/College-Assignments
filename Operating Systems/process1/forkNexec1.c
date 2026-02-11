#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int agrc,char *argv[]){
	char s[100];
	while(1){
		printf("Enter the name of the exucutable file : ");
		scanf("%s",s);
		printf("%s\n",s);
	}
}
