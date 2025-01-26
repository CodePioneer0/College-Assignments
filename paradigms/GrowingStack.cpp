#include <bits/stdc++.h>
using namespace std;

#define MAX_SIZE 100

typedef struct stack {
    int size;
    int count;
    int *arr;
} mystack;

inline int getMaxSize() { return MAX_SIZE; }

inline int currentSize(mystack &st) { return st.count + 1; }

inline int isEmpty(mystack &st) { return st.count == -1; }

inline int isFull(mystack &st) { return st.count == st.size - 1; }

int inflate(mystack &st) {
    //printf("Inflating the stack\n");
    st.size += 1;
    int *temp = new int[st.size];
    if (!temp) {
        return 0;
    }
    for (int i = 0; i <= st.count; i++) {
        temp[i] = st.arr[i];
    }
    delete[] st.arr;
    st.arr = temp;
    return 1;
}
int initialize(mystack &st, int stackSize) {
    if(stackSize>getMaxSize()) return 0;
    st.size = stackSize;
    st.count = -1;
    st.arr = new int[stackSize];
    if (st.arr) {
        return 1;
    } else {
        return 0;
    }
}

int push(mystack &st, int d) {
    if (isFull(st)) {
        if(st.size == getMaxSize()) {
            return 0;
        }
        else{
            if(!inflate(st)) {
                return 0;
            }
        }
    }
    st.arr[++st.count] = d;
    return 1;
}

int pop(mystack &st, int &d) {
    if (isEmpty(st)) {
        return 0;
    }
    d = st.arr[st.count];
    st.count--;
    return 1;
}




void printStack(mystack &st) {
    for (int i = 0; i <= st.count; i++) {
        printf("%d ", st.arr[i]);
    }
    printf("\n\n");
}
void stackEntry(mystack &st1,mystack &st2,mystack &st){
    if(isEmpty(st1) || isEmpty(st2)){
        cout<<"Stacks are initially empty!";
        return;
    }
    if(max(st1.size,st2.size)>100){
        cout<<"Stack can't be created due to insufficient space!"<<"\n";
        return;
    }
    
    int i = 1;
    int d = 0;
    while(!isEmpty(st1) && !isEmpty(st2)){
        if(i & 1){
            pop(st1,d);
            push(st,d);
        }
        else{
            pop(st2,d);
            push(st,d);
        }
        i++;
    }
    while(!isEmpty(st1)){
        pop(st1,d);
        push(st,d);
    }
    while(!isEmpty(st2)){
         pop(st2,d);
        push(st,d);
    }
}
int main() {
    srand(time(0));
    mystack st1,st2;
    int size1 = rand()%10+1;
    int size2 = rand()%10+1;
    if (!initialize(st1, size1)) {
        printf("Failed to initialize the stack1\n");
        return 1;
    }
    if (!initialize(st2, size2)) {
        printf("Failed to initialize the stack2\n");
        return 1;
    }
    for(int i=0;i<size1;i++){
        push(st1,rand()%100+1);
    }
    for(int i=0;i<size2;i++){
        push(st2,rand()%100+1);
    }
    printStack(st1);
    printStack(st2);
    mystack st;
    initialize(st,max(size1,size2));
    stackEntry(st1,st2,st);
    printStack(st);

    delete[] st1.arr;
    delete[] st2.arr;
    return 0;
}
