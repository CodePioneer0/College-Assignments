#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK 100

// Define Stack
char stack[MAX_STACK][3];
int top = -1;

void push(char* str) {
    if (top < MAX_STACK - 1) {
        strcpy(stack[++top], str);
    }
}

void pop() {
    if (top >= 0) {
        top--;
    }
}

// Convert Terminal to Column Index
int getCol(char c) {
    switch(c) {
        case 'a': return 0;
        case 'b': return 1;
        case '+': return 2;
        case '*': return 3;
        case '$': return 4;
        default:  return -1; // Invalid terminal
    }
}

// Convert Non-Terminal to Row Index
int getRow(char* nt) {
    if (strcmp(nt, "E") == 0) return 0;
    if (strcmp(nt, "E'") == 0) return 1;
    if (strcmp(nt, "T") == 0) return 2;
    if (strcmp(nt, "T'") == 0) return 3;
    if (strcmp(nt, "F") == 0) return 4;
    if (strcmp(nt, "F'") == 0) return 5;
    return -1;
}

int isTerminal(char* s) {
    if (strcmp(s, "a") == 0 || strcmp(s, "b") == 0 || 
        strcmp(s, "+") == 0 || strcmp(s, "*") == 0 || 
        strcmp(s, "$") == 0) {
        return 1;
    }
    return 0;
}

// Print Current Parse State
void printState(int ip, char* input, char* action) {
    char stackStr[200] = "";
    for (int i = 0; i <= top; i++) {
        strcat(stackStr, stack[i]);
    }
    printf("%-20s | %-20s | %-30s\n", stackStr, input + ip, action);
}

int main() {
    /* 
     LL(1) Parsing Table Encoding:
     Row: 0=E, 1=E', 2=T, 3=T', 4=F, 5=F'
     Col: 0=a, 1=b, 2=+, 3=*, 4=$
     Rules are numbered 1 to 10 (0 means Error)
    */
    int table[6][5] = {
        {  1,  1,  0,  0,  0 },  // E  (0)
        {  0,  0,  2,  0,  3 },  // E' (1)
        {  4,  4,  0,  0,  0 },  // T  (2)
        {  5,  5,  6,  0,  6 },  // T' (3)
        {  7,  8,  0,  0,  0 },  // F  (4)
        { 10, 10, 10,  9, 10 }   // F' (5)
    };

    char input[100];
    printf("Enter input string (ending with $): ");
    scanf("%s", input);

    // Initialize Stack with $ and Start Symbol (E)
    push("$");
    push("E");
    
    int ip = 0; // input pointer
    int isValid = 0;

    printf("\n%-20s | %-20s | %-30s\n", "Stack Contents", "Input Buffer", "Action Taken");
    printf("----------------------------------------------------------------------\n");

    while (top >= 0) {
        char* topSym = stack[top];
        char currInp = input[ip];
        char currInpStr[2] = {currInp, '\0'};
        char action[50] = "";

        if (isTerminal(topSym)) {
            if (strcmp(topSym, currInpStr) == 0) {
                if (currInp == '$') {
                    strcpy(action, "Match $ (Accept)");
                    printState(ip, input, action);
                    isValid = 1;
                    break;
                }
                sprintf(action, "Match %c", currInp);
                printState(ip, input, action);
                pop();
                ip++;
            } else {
                printState(ip, input, "Error: Mismatch");
                break;
            }
        } else {
            int row = getRow(topSym);
            int col = getCol(currInp);

            if (row == -1 || col == -1 || table[row][col] == 0) {
                printState(ip, input, "Error: Blank table entry");
                break;
            }

            int rule = table[row][col];
            
            // Format output string before modifying stack
            switch(rule) {
                case 1:  strcpy(action, "E -> T E'"); break;
                case 2:  strcpy(action, "E' -> + T E'"); break;
                case 3:  strcpy(action, "E' -> epsilon"); break;
                case 4:  strcpy(action, "T -> F T'"); break;
                case 5:  strcpy(action, "T' -> F T'"); break;
                case 6:  strcpy(action, "T' -> epsilon"); break;
                case 7:  strcpy(action, "F -> a F'"); break;
                case 8:  strcpy(action, "F -> b F'"); break;
                case 9:  strcpy(action, "F' -> * F'"); break;
                case 10: strcpy(action, "F' -> epsilon"); break;
            }
            printState(ip, input, action);
            
            // Pop the left hand side
            pop();
            
            // Push right hand side in REVERSE order
            switch(rule) {
                case 1:  push("E'"); push("T"); break;
                case 2:  push("E'"); push("T"); push("+"); break;
                case 3:  break; // epsilon
                case 4:  push("T'"); push("F"); break;
                case 5:  push("T'"); push("F"); break;
                case 6:  break; // epsilon
                case 7:  push("F'"); push("a"); break;
                case 8:  push("F'"); push("b"); break;
                case 9:  push("F'"); push("*"); break;
                case 10: break; // epsilon
            }
        }
    }

    printf("\nResult: ");
    if (isValid) {
        printf("Successfully Parsed (Valid)\n");
    } else {
        printf("Rejected (Syntax Error)\n");
    }

    return 0;
}