#include <iostream>
#include <cstring>
using namespace std;

#define MAX_SIZE 100

enum DataType { INT, FLOAT, STRUCT, STRING };

struct MyStruct {
    char name[50];
    int age;
};

union Data {
    int i;
    float f;
    MyStruct s;
    char* str;
};

struct mystack {
    int size;
    int count;
    DataType type;
    void* arr;
};

inline int getMaxSize() { return MAX_SIZE; }

inline int currentSize(mystack& st) { return st.count + 1; }

inline bool isEmpty(mystack& st) { return st.count == -1; }

inline bool isFull(mystack& st) { return st.count == st.size - 1; }

int inflate(mystack& st) {
    cout << "Inflating the stack\n";

    if (st.size == MAX_SIZE) {
        cout << "Stack has reached maximum size.\n";
        return 0;
    }

    int newSize = st.size +1; 
    void* temp = nullptr;

    switch (st.type) {
        case INT:
            temp = new int[newSize];
            memcpy(temp, st.arr, (st.count + 1) * sizeof(int));
            delete[] static_cast<int*>(st.arr);
            break;

        case FLOAT:
            temp = new float[newSize];
            memcpy(temp, st.arr, (st.count + 1) * sizeof(float));
            delete[] static_cast<float*>(st.arr);
            break;

        case STRUCT:
            temp = new MyStruct[newSize];
            memcpy(temp, st.arr, (st.count + 1) * sizeof(MyStruct));
            delete[] static_cast<MyStruct*>(st.arr);
            break;

        case STRING: {
            char** newA = new char*[newSize]; 
            char** oldA = static_cast<char**>(st.arr);

            for (int i = 0; i <= st.count; i++) {
                newA[i] = strdup(oldA[i]);  
            }

            temp = newA;
            for (int i = 0; i <= st.count; i++) {
                delete (oldA[i]); 
            }
            delete[] oldA; 
            break;
        }
    }
    if (!temp) return 0; 
    st.arr = temp;
    st.size = newSize;
    return 1;
}



int initialize(mystack& st, int stackSize, DataType type) {
    if (stackSize > getMaxSize()) return 0;
    st.size = stackSize;
    st.count = -1;
    st.type = type;

    switch (type) {
        case INT:
            st.arr = new int[stackSize];
            break;
        case FLOAT:
            st.arr = new float[stackSize];
            break;
        case STRUCT:
            st.arr = new MyStruct[stackSize];
            break;
        case STRING:
            st.arr = new char*[stackSize];
            break;
    }

    return st.arr != nullptr;
}

int push(mystack& st, Data d) {
    if (isFull(st)) {
        if (!inflate(st)) {
            return 0;
        }
    }
    switch (st.type) {
        case INT:
            static_cast<int*>(st.arr)[++st.count] = d.i;
            break;
        case FLOAT:
            static_cast<float*>(st.arr)[++st.count] = d.f;
            break;
        case STRUCT:
            static_cast<MyStruct*>(st.arr)[++st.count] = d.s;
            break;
        case STRING:
            static_cast<char**>(st.arr)[++st.count] = strdup(d.str);
            break;
    }
    return 1;
}

int pop(mystack& st, Data& d) {
    if (isEmpty(st)) {
        return 0;
    }

    switch (st.type) {
        case INT:
            d.i = static_cast<int*>(st.arr)[st.count--];
            break;
        case FLOAT:
            d.f = static_cast<float*>(st.arr)[st.count--];
            break;
        case STRUCT:
            d.s = static_cast<MyStruct*>(st.arr)[st.count--];
            break;
        case STRING:
            d.str = static_cast<char**>(st.arr)[st.count--];
            break;
    }

    return 1;
}

void printStack(mystack& st) {
    for (int i = 0; i <= st.count; i++) {
        switch (st.type) {
            case INT:
                cout << static_cast<int*>(st.arr)[i] << " ";
                break;
            case FLOAT:
                cout << static_cast<float*>(st.arr)[i] << " ";
                break;
            case STRUCT:
                cout << static_cast<MyStruct*>(st.arr)[i].name << " " << static_cast<MyStruct*>(st.arr)[i].age << " ";
                break;
            case STRING:
                cout << static_cast<char**>(st.arr)[i] << " ";
                break;
        }
    }
    cout << endl;
}
