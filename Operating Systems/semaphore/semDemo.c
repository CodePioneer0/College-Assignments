/* sem0.c */
#include <stdio.h>
#include <sys/types.h> /* for semget(2) ftok(3) semop(2) semctl(2) */
#include <sys/ipc.h> /* for semget(2) ftok(3) semop(2) semctl(2) */
#include <sys/sem.h> /* for semget(2) semop(2) semctl(2) */
#include <unistd.h> /* for fork(2) sleep(3)*/

#include <stdlib.h> /* for exit(3) */



int main(int argc,char *argv[]) {
	key_t mykey;
	pid_t pid;
	char *str = argv[1];
	char id = atoi(argv[2]);
	char semnum = atoi(argv[4]);
	int semid;

	// key_t ftok(const char *pathname, int proj_id);
	//mykey = ftok("/home/manas/Documents/Operating Systems/samples/sem/sem1.c", 1);
	mykey = ftok(str, id);
	
	if (mykey == -1) {
		perror("ftok() failed");
		exit(1);
	}

	semid = semget(mykey, semnum, IPC_CREAT | 0777);
		// mykey - returns id for the semaphore set associated with mykey 
		// nsems - semaphore set shoud contain nsems semaphores
		// IPC_CREAT - Create the semaphore set if it is NOT already created
		// 0777 (octal) ie 111 111 111 (binary) - all rwx permission for UGO (user/owner, Group members, Others) 

	if(semid == -1) {
		perror("semget() failed");
		exit(1);
	}

}
