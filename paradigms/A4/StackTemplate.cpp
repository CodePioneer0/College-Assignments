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
int main(){
    mystack<int>s1(3);
    s1.push(1);
    s1.push(2);
    s1.push(3);
    cout<<"Interger Stack\n";
    s1.display();
    mystack<double>s2(3);
    s2.push(1.1);
    s2.push(2.2);
    s2.push(3.3);
    cout<<"Double Stack\n";
    s2.display();
   mystack<short>s3(3);
    s3.push(1);
    s3.push(2);
    s3.push(3);
    cout<<"Short Stack\n";
    s3.display();
    mystack<float>s4(3);
    s4.push(1.1);
    s4.push(2.2);
    s4.push(3.3);
    cout<<"Float Stack\n";
    s4.display();
    mystruct ms1,ms2,ms3;
    ms1.a = 1;
    ms2.a = 2;
    ms3.a = 3;
    mystack<mystruct>s5(3);
    s5.push(ms1);
    s5.push(ms2);
    s5.push(ms3);
    cout<<"Struct Stack\n";
    s5.display();
    cout<<"Number of instances: "<<s1.instCount()<<endl;
    return 0;
}
