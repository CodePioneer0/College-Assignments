#include <iostream>
#include <cstring>
using namespace std;

#define MAX_SIZE 100

template <typename T>
struct mystack {
    int size;
    int count;
    T* arr;
};
struct MyStruct {
    char name[50];
    int age;
};

inline int getMaxSize() {   return MAX_SIZE; }

template <typename T>
inline int currentSize(mystack<T>& st) { return st.count + 1; }

template <typename T>
inline bool isEmpty(mystack<T>& st) { return st.count == -1; }

template <typename T>
inline bool isFull(mystack<T>& st) { return st.count == st.size - 1; }

template <typename T>
int inflate(mystack<T>& st) {
    cout << "Inflating the stack\n";
    if (st.size == MAX_SIZE) {
        cout << "Stack has reached maximum size.\n";
        return 0;
    }

    int newSize = st.size + 1;
    T* temp = new T[newSize];
    if (!temp) return 0;
    for (int i = 0; i <= st.count; i++) {
        temp[i] = st.arr[i];
    }
    delete[] st.arr;
    st.arr = temp;
    st.size = newSize;
    return 1;
}

template <typename T>
int initialize(mystack<T>& st, int stackSize) {
    if (stackSize > getMaxSize()) return 0;
    st.size = stackSize;
    st.count = -1;
    st.arr = new T[stackSize];
    return st.arr != nullptr;
}

template <typename T>
int push(mystack<T>& st, T d) {
    if (isFull(st)) {
        if (!inflate(st)) {
            return 0;
        }
    }
    st.arr[++st.count] = d;
    return 1;
}

template <typename T>
int pop(mystack<T>& st, T& d) {
    if (isEmpty(st)) {
        return 0;
    }
    d = st.arr[st.count--];
    return 1;
}

template <typename T>
void printStack(mystack<T>& st) {
    for (int i = 0; i <= st.count; i++) {
        cout << st.arr[i] << " ";
    }
    cout << endl;
}

void printStack(mystack<MyStruct>& st) {
    for (int i = 0; i <= st.count; i++) {
        cout << "Name: " << st.arr[i].name << ", Age: " << st.arr[i].age << " ";
    }
    cout << endl;
}