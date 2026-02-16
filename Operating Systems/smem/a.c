#include <stdio.h>
#include <unistd.h> /* for fork() */
#include <sys/wait.h> /* for wait() */
#include <sys/types.h> /* for wait() kill(2)*/
#include <sys/ipc.h> /* for shmget() shmctl() */
#include <sys/shm.h> /* for shmget() shmctl() */

#include <signal.h> /* for signal(2) kill(2) */

#include <errno.h> /* for perror */

#include <stdlib.h>
#include <time.h> /* for time() */
struct shstruct{
	int flag;
	int n;
};
int facto(int n){
	if(n==0) return 1;
	int fact = 1;
	for(int i=2;i<=n;i++){
		fact = fact*i;
	}
	return fact;
}


int shmid; /* stores the id of the  shared memory segment as returned by shmget(). this variable is defined globally so that signal handler can access it for releasing the shared memory segment. */

/* following is a signal handler for the keypress ^C, that is, ctrl-c */
typedef void (*sighandler_t)(int);
void releaseSHM(int signum) {
        int status;
        // int shmctl(int shmid, int cmd, struct shmid_ds *buf); /* Read the manual for shmctl()
        status = shmctl(shmid, IPC_RMID, NULL); /* IPC_RMID is the command for destroying the shared memory*/
        if (status == 0) {
                fprintf(stderr, "Remove shared memory with id = %d.\n", shmid);
        } else if (status == -1) {
                fprintf(stderr, "Cannot remove shared memory with id = %d.\n", shmid);
        } else {
                fprintf(stderr, "shmctl() returned wrong value while removing shared memory with id = %d.\n", shmid);
        }

        // int kill(pid_t pid, int sig);
        status = kill(0, SIGKILL);
        if (status == 0) {
                fprintf(stderr, "kill susccesful.\n"); /* this line may not be executed :P WHY?*/
        } else if (status == -1) {
                perror("kill failed.\n");
                fprintf(stderr, "Cannot remove shared memory with id = %d.\n", shmid);
        } else {
                fprintf(stderr, "kill(2) returned wrong value.\n");
        }                                                                                                                       
}      
                                                                                                                      

int main() {
        int status;
        pid_t pid=0;
        pid_t p1=0;
        srand(time(NULL));
        sighandler_t shandler;


        /* install signal handler */
        // sighandler_t signal(int signum, sighandler_t handler);
        shandler =  signal(SIGINT, releaseSHM); /* should we call this seperately in parent and child process */



        // int shmget(key_t key, size_t size, int shmflg);

        shmid =  shmget(IPC_PRIVATE, sizeof(struct shstruct), IPC_CREAT | 0777);

        if (shmid == -1) { /* shmget() failed() */
                perror("shmget() failed: ");
                exit (1);
        }

        printf("shmget() returns shmid = %d.\n", shmid);

        p1 = fork();
        if (p1 == 0) { /* child process */

                int i;
                struct shstruct *pi_child;

                // void *shmat(int shmid, const void *shmaddr, int shmflg);
                pi_child = shmat(shmid, NULL, 0);
                if (pi_child == (void *)-1) { /* shmat fails */
                        perror("shmat() failed at child: ");
                        exit (1);
                }

                while(1) {
                        printf("Child Reads n : %d and flag : %d.\n", pi_child->n,pi_child->flag);
			if(pi_child->flag==1){
				pi_child->flag = 0;
			        pi_child->n = facto(pi_child->n);
			}	
			printf("Child writes n : %d and flag : %d.\n",pi_child->n,pi_child->flag);
                        getchar();    
                }
                exit(0);

        } else { /* parent process */
                int i;
                struct shstruct *pi_parent;

                // void *shmat(int shmid, const void *shmaddr, int shmflg);
                pi_parent = shmat(shmid, NULL, 0);
                if (pi_parent == (void *)-1) { /* shmat fails */
                        perror("shmat() failed at parent: ");
                        exit (1);
                }

                while(1) {
			if(pi_parent->flag == -1 || pi_parent->flag == 0){
				pi_parent->n = rand()%10 + 1;
				pi_parent->flag = 1;
			}
                        printf("Parent writes n : %d and flag : %d.\n", pi_parent->n,pi_parent->flag);
                        getchar();
                }
                pid = wait(&status);
                printf("pid = %d status = %d!\n", pid, status);
                exit(0);
        }   
}
