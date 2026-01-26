/* fork1.c */

#include <stdio.h>

#include <unistd.h>

int main() {

          printf("Parent Only\n");    /* Executed by "parent" process only.*/

          fork();                            /* Executed by "parent" process only.*/

          printf("Both Parent and Child\n");      /* Executed by both  parent and child processes .*/

}
