#include<iostream>
using namespace std;

class mystack{
    int **arr;
    int topIndex;
    int currentSize;
    int rowCount;
    int rowSize;
    static const int MaxSize;
    static int instanceCount;
    static const int maxInstance;

    inline bool isEmpty() const{
        return topIndex==-1;
    }
    inline int getMaxSize() const{
        return MaxSize;
    }
    inline int currSize() const{
        return topIndex+1;
    }
public:
    static int instCount(){
        return instanceCount;
    }
   //Default Constructor
    mystack(int size) : topIndex(-1),currentSize(size),rowCount(1),rowSize(size){
        if(instanceCount>=maxInstance){
            cout<<"Cannot create more instances\n";
            return;
        }
        if(currentSize>MaxSize){
            cout<<"Overflow!\n";
            return;
        }
        arr = new int*[MaxSize/rowSize + 1];
        arr[0] = new int[rowSize];
        for(int i=1;i<MaxSize/rowSize + 1;i++){
            arr[i] = nullptr;
        }
        instanceCount++; 
    }
    //Copy Constructor
    mystack(const mystack &st) : topIndex(st.topIndex),currentSize(st.currentSize),rowCount(st.rowCount),rowSize(st.rowSize){
        
        this->arr = new int*[MaxSize/rowSize + 1];

        for(int i=0;i<rowCount;i++){
            if(st.arr[i]!=nullptr){
                this->arr[i] = new int[rowSize];
                for(int j=0;j<rowSize && (i*rowSize+j<=topIndex);j++){
                    this->arr[i][j] = st.arr[i][j];
                }
            }
            else{
                this->arr[i] = nullptr;
            }
        }
        for(int i=rowCount;i<MaxSize/rowSize + 1;i++){
            this->arr[i] = nullptr;
        }
        instanceCount++;
    }
    //Destructor
    ~mystack(){
        for(int i=0;i<rowCount;i++){
            delete[] arr[i];
        }
        delete[] arr;
        instanceCount--;
    }
    //Assignment Operator
    mystack& operator=(const mystack &st){
        if(this == &st){
            return *this;
        }
        for(int i=0;i<rowCount;i++){
            delete[] arr[i];
        }
        delete[] arr;
        this->topIndex = st.topIndex;
        this->currentSize = st.currentSize;
        this->rowCount = st.rowCount;
        this->rowSize = st.rowSize;
        this->arr = new int*[MaxSize/rowSize + 1];
        for(int i=0;i<rowCount;i++){
            if(st.arr[i]!=nullptr){
                this->arr[i] = new int[rowSize];
                for(int j=0;j<rowSize && (i*rowSize+j)<=topIndex;j++){
                    this->arr[i][j] = st.arr[i][j];
                }
            }
            else{
                this->arr[i] = nullptr;
            }
        }
        for(int i=rowCount;i<MaxSize/rowSize + 1;i++){
            this->arr[i] = nullptr;
        }
        return *this;
    }
    bool push(const int &data) {
        if (topIndex + 1 == MaxSize) {
            cout << "Overflow!\n";
            return false;
        }
        
        if (topIndex + 1 == currentSize) {
            if(!inflate()){
                return false;
            }
        }
        topIndex++;
        int row = topIndex / rowSize;
        int col = topIndex % rowSize;
        arr[row][col] = data;
        return true;
    }
    bool push(const int &data1,const int &data2){
        if(push(data1)){
            return push(data2);
        }
        return false;
    }
    bool pop(int &data) {
        if (isEmpty()) {
            cout << "Underflow!\n";
            return false;
        }
        int row = topIndex / rowSize;
        int col = topIndex % rowSize;
        data = arr[row][col];
        topIndex--;
        return true;
    }
    bool inflate() {
        cout << "Inflating - New Row\n";
        if (currentSize + rowSize > MaxSize) {
            cout << "Cannot inflate\n";
            return false;
        }

        if (arr[rowCount] == nullptr) {
            arr[rowCount] = new int[rowSize];
        }
        rowCount++;
        currentSize += rowSize;
        return true;
    }
    void display() const{
        for(int i=0;i<=topIndex;i++){
            int row = i/rowSize;
            int col = i%rowSize;
            cout<<arr[row][col]<<" ";
        }
        cout<<endl;
    }    
    
    friend const mystack operator+(const mystack &, const mystack &);

};



const mystack operator+(const mystack &s1, const mystack &s2){
    if(mystack::instanceCount >= mystack::maxInstance){
        cout<<"Cannot create more instances\n";
        return s1;
    }
    int size = s1.currSize() + s2.currSize();
    if(size>mystack :: MaxSize){
        cout<<"Cannot create more instances\n";
        return s1;
    }
    mystack s3(size);
    for(int i=0;i<s1.currSize();i++){
        int row = i/s1.rowSize;
        int col = i%s1.rowSize;
        s3.push(s1.arr[row][col]);      
    }
    for(int i=0;i<s2.currSize();i++){
        int row = i/s2.rowSize;
        int col = i%s2.rowSize;
        s3.push(s2.arr[row][col]);
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