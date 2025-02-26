#include<iostream>
using namespace std;

template <typename T>
class mystack{
    T *arr;
    int topIndex;
    int currentSize;
    static const int MaxSize;
    static int instanceCount;
public:
   //Default Constructor
    mystack(int size) : topIndex(-1),currentSize(size){
        if(currentSize>MaxSize){
            cout<<"Overflow!\n";
            return;
        }
        arr = new T[currentSize];
        instanceCount++; 
    }
    //Copy Constructor
    mystack(const mystack &st){
        this->topIndex = st.topIndex;
        this->currentSize = st.currentSize;
        this->arr = new T[currentSize];
        for(int i=0;i<=topIndex;i++){
            this->arr[i] = st.arr[i];
        }
        instanceCount++;
    }
    //Destructor
    ~mystack(){
        delete[] arr;
        instanceCount--;
    }
    //Assignment Operator
    mystack& operator=(const mystack &st){
        if(this == &st){
            return *this;
        }
        delete[] arr;
        this->topIndex = st.topIndex;
        this->currentSize = st.currentSize;
        this->arr = new T[currentSize];
        for(int i=0;i<=topIndex;i++){
            this->arr[i] = st.arr[i];
        }
        return *this;
    }

    void push(const T& data){
        if(topIndex+1 == MaxSize) return;
        if(topIndex == currentSize-1){
            inflate();
        }
        arr[++topIndex] = data;
    }

    T pop(){
        if(isEmpty()){
            cout<<"Underflow!\n";
        }
        return arr[topIndex--];
    }
    int getMaxSize(){
        return MaxSize;
    }
    int currSize() const{
        return topIndex+1;
    }
    int isEmpty(){
        return topIndex == -1;
    }
    void inflate(){
        cout<<"Inflating\n";
        if(topIndex+1 == MaxSize){
            cout<<"Max size reached\n";
            return;
        }
        int newSize = currentSize+1;
        T *temp = new T[newSize];
        if(temp == NULL){
            cout<<"Memory Error\n";
            return;
        }
        for(int i=0;i<=topIndex;i++){
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
        currentSize = newSize;
    }
    void display(){
        for(int i=0;i<=topIndex;i++){
            cout<<arr[i]<<' ';
        }
        cout<<endl;
    }
    static int instCount(){
        return instanceCount;
    }


};
template <typename T>
const int mystack<T> :: MaxSize = 50;
template <typename T>
int mystack<T> :: instanceCount = 0;
struct mystruct {
    int a;
    friend ostream& operator<<(ostream& os, const mystruct& ms) {
        os << ms.a;
        return os;
    }
};