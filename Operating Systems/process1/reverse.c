#include <stdio.h>
#include <string.h>
void reverse(char *s){
	int n = strlen(s);
	for(int i=0;i<n/2;i++){
		char temp = s[i];
		s[i] = s[n-i-1];
		s[n-i-1] = temp;
	}
}
int main(int argc,char *argv[]){
    if(argc<2){
        printf("Strings not provied!\n");
        return 1;
    }
    reverse(argv[1]);
    printf("Reversed String : %s\n",argv[1]);
    return 0;
}