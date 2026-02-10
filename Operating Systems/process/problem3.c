#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void sort(int n, int arr[]){
	for (int i = 0; i < n - 1; i++){
		for (int j = 0; j < n - i - 1; j++){
			if (arr[j + 1] < arr[j]){
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
int main(int argc, char *argv[]){
	int n;
	printf("Enter the number n : ");
	scanf("%d", &n);
	int arr[n];
	int parentArr[n];
	for (int i = 0; i < n; i++){
		printf("The %dth number : ", i + 1);
		scanf("%d", &arr[i]);
	}
	sort(n, arr);
	printf("Sorted Array : \n");
	// Sorted Array
	for (int i = 0; i < n; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
	// Creating ith Process to Output ith Largest Number
	for (int i = 0; i < n; i++){
		pid_t p;
		p = fork();
		if (p == 0){
			printf("%dth Largest : %d", i + 1, arr[n - i - 1]);
			printf("\n");
			int num = arr[n - i - 1];
			exit(num);
		}
		else{
			int cid;
			int plstatus;
			cid = wait(&plstatus);
			plstatus = plstatus >> 8;
			parentArr[i] = plstatus;
			printf("Parent Getting the value from child : %d\n", parentArr[i]);
		}
	}
	return 0;
}
