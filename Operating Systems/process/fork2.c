/* fork2.c */

#include <stdio.h>

#include <unistd.h>

int main() {
                 pid_t p;
                 printf("Parent Only\n");    /* Executed by "parent" process only.*/
                 p = fork();                         /* fork() is executed  by "parent" process only.*/
                                                        /* p = <return value from fork()> is executed  by both parent and child  processes.*/

                                                       /* Note that

                                                         (i) in the parent process the <return value from fork()> is the pid of the child process

                                                         (ii) in the child process the <return value from fork()> is 0 (zero) */

                 if (p == 0) {                   /* executed  by both parent and child  processes.*/

                                                    /* "p == 0"  evaluates to true only in the child process (p there contains 0) */

                        printf("Child process!"); /* Hence, executed by the child process only.*/
                 } else {                         /*p == 0"  evaluates to false in the parent process (p there contains the pid of the child process) */                             

                        printf("Parent process!"); /* Hence, executed by the parent process only.*/
                 }

                 printf("Both Parent and Child!\n");    /* Executed by both parent and child processes.*/

 }
