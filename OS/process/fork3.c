 

/* fork3.c */

#include <stdio.h>

#include <unistd.h>

int main() {
                 pid_t p;

                 p = fork();

                 if (p == 0) {

			 printf("Child Process Return Value : %d\n",p);
                       /* program segment B1 to be executed by the child process,
                       
		       	  keep you own code here for testing! */
                 } else {
			 printf("Child id returned by fork(): %d\n",p);
                       /* program segment B2 to be executed by the parent process

                          keep you own code here for testing! */
                 }
		 printf("Both Parent And Child!\n");

                /* program segment B3 to be executed by both

                   the parent process (if not B2 has terminated it) and

                  the child process (if not B1 has terminated it) ,

                  keep you own code here for testing! */
}
