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

    inline bool isEmpty() const{
        return topIndex==-1;
    }
public:
   //Default Constructor
    mystack(int size) : topIndex(-1),currentSize(size),rowCount(1),rowSize(size){
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
    mystack(const mystack &st): topIndex(st.topIndex),currentSize(st.currentSize),rowCount(st.rowCount),rowSize(st.rowSize){
        

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
            if(arr[i] != nullptr){
                delete[] arr[i];
            }
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
    inline int getMaxSize() const{
        return MaxSize;
    }
    inline int currSize() const{
        return topIndex+1;
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
    static int instCount(){
        return instanceCount;
    }

};

const int mystack :: MaxSize = 50;
int mystack :: instanceCount = 0;