#include <stdio.h>
#include <stdlib.h> 

typedef struct myStack {
    int maxSize;
    int count;
    int *element;
} myStack;

int initIntegerStack(myStack *st, int stackSize) {
    st->maxSize = stackSize;
    st->count = -1;
    st->element = (int *)malloc(stackSize * sizeof(int));
    if (st->element) {
        return 1;
    } else {
        return 0;
    }
}

int freeIntegerStack(myStack *st) {
    if (st) {
        free(st->element);
        st->element = NULL;
        return 1;
    }
    return 0;
}

int isIntegerStackFull(myStack *st) {
    if (st->count + 1 == st->maxSize) {
        return 1;
    }
    return 0;
}

int isIntegerStackEmpty(myStack *st) {
    if (st->count == -1) {
        return 1;
    }
    return 0;
}

int pushIntegerStack(myStack *st, int d) {
    if (isIntegerStackFull(st)) {
        return 0;
    }
    st->element[++st->count] = d;
    return 1;
}

int popIntegerStack(myStack *st, int *d) {
    if (isIntegerStackEmpty(st)) {
        return 0;
    }
    *d = st->element[st->count];
    st->count--;
    return 1;
}

int enqueue(myStack *s1, int a) { 
    if(isIntegerStackFull(s1))return 0;
    pushIntegerStack(s1, a);
    return 1;
}

int dequeue(myStack *s1, myStack *s2, int *d) {
    if (isIntegerStackEmpty(s1)) {
        return 0;
    }
    while (!isIntegerStackEmpty(s1)) {
        int e;
        popIntegerStack(s1, &e);
        pushIntegerStack(s2, e);
    }
    popIntegerStack(s2, d);
    while (!isIntegerStackEmpty(s2)) {
        int e;
        popIntegerStack(s2, &e);
        pushIntegerStack(s1, e);
    }
    return 1; 
}

int main() {
    myStack s1;
    myStack s2;
    int maxSize;
    printf("Enter the max length of stack: ");
    scanf("%d", &maxSize);
    if (initIntegerStack(&s1, maxSize) && initIntegerStack(&s2, maxSize)) {
        printf("Stack Creation Successful!\n");
    } else {
        printf("Stack Creation Failed!\n");
        return 1;
    }

    // Queue implementation by Stack
    printf("1. Enqueue\n2. Dequeue\n3. Exit\n");
    int n;
    do {
        printf("Enter the option: ");
        scanf("%d", &n);
        if (n == 1) {
            int a;
            printf("Enter the element: ");
            scanf("%d", &a);
            if(enqueue(&s1, a)){
                printf("Successful Enqueue!\n");
            }
            else{
                printf("Overflow!\n");
            }
        } else if (n == 2) {
            int a;
            if (dequeue(&s1, &s2, &a)) {
                printf("Dequeue is successful!\n");
                printf("Element: %d\n", a);
            } else {
                printf("Underflow!\n");
            }
        }
    } while (n != 3);
    printf("Released Allocated Memory!\n");
    freeIntegerStack(&s1);
    freeIntegerStack(&s2);

    return 0;
}
