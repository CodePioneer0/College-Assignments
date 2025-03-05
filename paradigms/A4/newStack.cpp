#include<iostream>
using namespace std;

class mystack{
    int *arr;
    int topIndex;
    int currentSize;
    static const int MaxSize;
    static int instanceCount;
    static const int maxInstance;
public:
   //Default Constructor
    mystack(int size) : topIndex(-1),currentSize(size){
        if(instanceCount>=maxInstance){
            cout<<"Max instance reached\n";
            arr = NULL;
            return;
        }
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
    friend mystack operator+(const mystack &,const mystack &);
};

mystack operator+(const mystack &s1, const mystack &s2){
    mystack s3(s1.currentSize+s2.currentSize);
    for(int i=0;i<=s1.topIndex;i++){
        s3.push(s1.arr[i]);
    }
    for(int i=0;i<=s2.topIndex;i++){
        s3.push(s2.arr[i]);
    }
    return s3;
}

const int mystack :: MaxSize = 50;
int mystack :: instanceCount = 0;
const int mystack :: maxInstance = 5;

int main(){
    mystack s1(5);
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(5);
    s1.display();
    mystack s2(5);
    s2.push(6);
    s2.push(7);
    s2.push(8);
    s2.push(9);
    s2.push(10);
    s2.display();
    mystack s3 = s1+s2;
    s3.display();
    cout<<"Number of instances : "<<mystack::instCount()<<endl;
    mystack s4(3);
    cout<<"Number of instances : "<<mystack::instCount()<<endl;
    mystack s5(2);
    cout<<"Number of instances : "<<mystack::instCount()<<endl;
    mystack s6(6);
    cout<<"Number of instances : "<<mystack::instCount()<<endl;
    return 0;
}