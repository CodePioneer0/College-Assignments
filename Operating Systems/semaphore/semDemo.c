
#include <stdio.h>
#include <sys/types.h> /* for semget(2) ftok(3) semop(2) semctl(2) */
#include <sys/ipc.h> /* for semget(2) ftok(3) semop(2) semctl(2) */
#include <sys/sem.h> /* for semget(2) semop(2) semctl(2) */
#include <unistd.h> /* for fork(2) sleep(3)*/

#include <string.h>

#include <stdlib.h> /* for exit(3) */
struct sembuf Pop; /* structure capturing the operation of decrementing a semaphore's value */
struct sembuf Vop; /* structure capturing the operation of incrementing a semaphore's value */

#define P(sid) semop(sid, &Pop, 1); /* P(sid) decrements the value of the 1st semaphore of the set sid */
#define V(sid) semop(sid, &Vop, 1); /* V(sid) increments the value of the 1st semaphore of the set sid */

int main(int argc,char *argv[]) {
	if(argc<4){
		printf("Usage: %s <pathname> <proj_id> <sem_num>\n",argv[0]);
		exit(1);
	}
	key_t mykey;
	int status;
	int semid;
	char *filePath = argv[1];
	int proj_id = atoi(argv[2]);
	char *command = argv[3];
	union semun {
		int              val;    /* Value for SETVAL */
		struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
		unsigned short  *array;  /* Array for GETALL, SETALL */
		struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
	} setvalArg;
	mykey = ftok(filePath,proj_id);
	if(mykey==-1){
		perror("ftok() failed!\n");
		exit(1);
	}
	printf("Key : %d file %s projectId : %d\n",mykey,filePath,proj_id);
	if(strcmp(command,"create")==0){
		int semnum = atoi(argv[4]);
		semid = semget(mykey,semnum,IPC_CREAT|0777);
		if(semid==-1){
			perror("semget() failed!\n");
			exit(1);
		}
		printf("Semaphore created with id : %d\n",semid);
	}
	else if(strcmp(command,"set")==0){
		int semnum = atoi(argv[4]);
		int sem_val = atoi(argv[5]);
		int semid = semget(mykey,0,0);
		if(semid==-1){
			perror("semget() failed!\n");
			exit(1);
		}
		setvalArg.val = sem_val;
		status = semctl(semid,semnum,SETVAL,setvalArg);
		if(status==-1){
			perror("semctl() failed!\n");
			exit(1);
		}
		printf("Value of semaphore number %d set to %d\n",semnum,sem_val);
	}
	else if(strcmp(command,"get")==0){
		int semnum = atoi(argv[4]);
		semid = semget(mykey,0,0);
		if(semid==-1){
			perror("semget() failed!\n");
			exit(1);
		}
		int sem_val = semctl(semid,semnum,GETVAL);
		if(sem_val==-1){
			perror("semctl() failed!\n");
			exit(1);
		}
		printf("Value of semaphore number %d is : %d\n",semnum,sem_val);
	}
	else if(strcmp(command,"inc")==0){
		int semnum = atoi(argv[4]);
		semid = semget(mykey,0,0);
		if(semid==-1){
			perror("semget() failed!\n");
			exit(1);
		}
		Vop.sem_num = semnum;
		Vop.sem_op = 1;
		Vop.sem_flg = 0;
		status = V(semid);
		if(status==-1){
			perror("semop() failed!\n");
			exit(1);
		}
		printf("Incremented semaphore number %d\n",semnum);
	}
	else if(strcmp(command,"dec")==0){
		int semnum = atoi(argv[4]);
		semid = semget(mykey,0,0);
		if(semid==-1){
			perror("semget() failed!\n");
			exit(1);
		}
		Pop.sem_num = semnum;
		Pop.sem_op = -1;
		Pop.sem_flg = 0;
		status = P(semid);
		if(status==-1){
			perror("semop() failed!\n");
			exit(1);
		}
		printf("Decremented semaphore number %d\n",semnum);
	}
	else if(strcmp(command,"rm")==0){
		semid = semget(mykey,0,0);
		if(semid==-1){
			perror("semget() failed!\n");
			exit(1);
		}
		status = semctl(semid,0,IPC_RMID);
		if(status==-1){
			perror("semctl() failed!\n");
			exit(1);
		}
		printf("Semaphore set destroyed with id %d\n",semid);
	}
	else if(strcmp(command,"listp")==0){
		semid = semget(mykey,0,0);
		if(semid==-1){
			perror("semget() failed!\n");
			exit(1);
		}
		if(argc>=5){
			int semnum = atoi(argv[4]);
			int lastpid = semctl(semid,semnum,GETPID);
			int IncCount = semctl(semid,semnum,GETNCNT);
			int ZeroCount = semctl(semid,semnum,GETZCNT);
			printf("Semaphore number %d : lastpid = %d, IncCount = %d, ZeroCount = %d\n",semnum,lastpid,IncCount,ZeroCount);
		}
		else{
			int nsems = semctl(semid,0,GETNCNT);
			for(int i=0;i<nsems;i++){
				int lastpid = semctl(semid,i,GETPID);
				int IncCount = semctl(semid,i,GETNCNT);
				int ZeroCount = semctl(semid,i,GETZCNT);
				printf("Semaphore number %d : lastpid = %d, IncCount = %d, ZeroCount = %d\n",i,lastpid,IncCount,ZeroCount);
			}
		}
	}
	else{
		printf("Invalid command!\n");
		exit(1);
	}
	return 0;
}