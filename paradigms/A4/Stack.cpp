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

int main(){
    mystack s1(6);
    mystack s2(5);
    for(int i=1;i<=6;i++){
        s1.push(i);
    }
    for(int i=0;i<5;i++){
        s2.push(i+7);
    }
    cout<<"Stack 1: ";
    s1.display();
    cout<<"Stack 2: ";
    s2.display();
    mystack s3(11);
    int i=1;
    while(!s1.isEmpty() && !s2.isEmpty()){
        if(i%2==0){
            s3.push(s2.pop());
        }else{
            s3.push(s1.pop());
        }
        i++;
    }
    while(!s1.isEmpty()){
        s3.push(s1.pop());
    }
    while(!s2.isEmpty()){
        s3.push(s2.pop());
    }
    cout<<"Stack 3: ";
    s3.display();
    mystack s4 = s3;
    cout<<"Created using copy constructor\n";
    cout<<"Stack 4: ";
    s4.display();
    mystack s5(6);

    s5 = s3;
    cout<<"Created using assignment operator\n";
    cout<<"Stack 5: ";
    s5.display();
    mystack s6(6);
    for(int i=1;i<=10;i++){
        s6.push(i);
    }
    cout<<"Stack 6: ";
    s6.display();
    cout<<"Instance Count: "<<mystack::instCount()<<endl;
}