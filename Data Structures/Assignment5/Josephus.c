#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct person {
    int id;
    struct person *next;
};

struct person* createCircle(int N) {
    struct person *head = NULL, *tail = NULL;
    for (int i = 1; i <= N; i++) {
        struct person *newPerson = (struct person*)malloc(sizeof(struct person));
        newPerson->id = i;
        if (head == NULL) {
            head = newPerson;
            tail = newPerson;
        } else {
            tail->next = newPerson;
            tail = newPerson;
        }
    }
    tail->next = head;
    return head;
}

void playGame(int N, int S) {
    struct person *circle = createCircle(N);
    struct person *current = circle, *prev = NULL;
    
    while (N > 1) {
        for (int i = 1; i < S; i++) {
            prev = current;
            current = current->next;
        }
        
        printf("Person %d is evicted\n", current->id);
        prev->next = current->next;
        free(current);
        current = prev->next;
        N--;
    }
    
    printf("The winner is Person %d\n", current->id);
    free(current);
}

int main() {
    int N, S;
    printf("Enter the number of people: ");
    scanf("%d", &N);
    printf("Enter the number of people to skip: ");
    scanf("%d", &S);
    
    playGame(N, S);
    
    return 0;
}
