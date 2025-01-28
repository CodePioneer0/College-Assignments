#include <iostream>
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
    cout<<"Inflating the stack\n";
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