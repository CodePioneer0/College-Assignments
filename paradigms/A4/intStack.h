#include<iostream>
using namespace std;

class mystack{
    int *arr;
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
        arr = new int[currentSize];
        instanceCount++; 
    }
    //Copy Constructor
    mystack(const mystack &st){
        this->topIndex = st.topIndex;
        this->currentSize = st.currentSize;
        this->arr = new int[currentSize];
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
        this->arr = new int[currentSize];
        for(int i=0;i<=topIndex;i++){
            this->arr[i] = st.arr[i];
        }
        return *this;
    }

    void push(int data){
        if(topIndex+1 == MaxSize) return;
        if(topIndex == currentSize-1){
            inflate();
        }
        arr[++topIndex] = data;
    }

    int pop(){
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
        return topIndex==-1;
    }
    void inflate(){
        cout<<"Inflating\n";
        if(topIndex+1 == MaxSize){
            cout<<"Max size reached\n";
            return;
        }
        int newSize = currentSize+1;
        int *temp = new int[newSize];
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

const int mystack :: MaxSize = 50;
int mystack :: instanceCount = 0;