#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct person {
    int id;
    struct person *next;
    struct person *prev;  
};

struct person* createCircle(int N) {
    struct person *head = NULL, *tail = NULL;
    for (int i = 1; i <= N; i++) {
        struct person *newPerson = (struct person*)malloc(sizeof(struct person));
        newPerson->id = i;
        if (head == NULL) {
            head = newPerson;
            tail = newPerson;
            head->prev = tail;
            tail->next = head;
        } else {
            tail->next = newPerson;
            newPerson->prev = tail;
            tail = newPerson;
            tail->next = head;
            head->prev = tail;
        }
    }
    return head;
}

void playGame(int N) {
    struct person *circle = createCircle(N);
    struct person *current = circle;
    
    srand(time(NULL)); 
    
    while (N > 1) {
        int S = rand() % 20 - 10;
        int abS = abs(S);
        
        printf("Skipping %d people ", abS);
        if (S >= 0) {
            printf("(clockwise) : \n");
            for (int i = 0; i < abS; i++) {
                current = current->next;
            }
        } else {
            printf("(anticlockwise) :\n");
            for (int i = 0; i < abS; i++) {
                current = current->prev;
            }
        }
        
        printf("Person %d is evicted\n\n", current->id);
        struct person *delNode = current;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        current = current->next;
        free(delNode);
        N--;
    }
    
    printf("The winner is Person %d\n", current->id);
    free(current);
}

int main() {
    int N;
    printf("Enter the number of people: ");
    scanf("%d", &N);
    
    playGame(N);
    
    return 0;
}
