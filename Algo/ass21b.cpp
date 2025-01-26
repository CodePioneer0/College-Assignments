#include <iostream>
#include<vector>
#include<random>
using namespace std;
int compare = 0;
void generator(int arr[],int &n){
    for(int i=0;i<n;i++){
        arr[i] = rand()%10000+1; 
    }
}

int DivideAndConquerMax(int arr[], int size) {
    if(size==1) return arr[0];
    if(size==2){
        compare++;
        if(arr[0]>arr[1]) return arr[0];
        else return arr[1];
    }
    int mid = size/2;
    int left =  DivideAndConquerMax(arr,mid);
    compare++;
    int right = DivideAndConquerMax(arr+mid,size-mid);
    compare++;
    if(right>left) return right;
    else return left;
}
int DivideAndConquerMin(int arr[], int size) {
    if(size==1) return arr[0];
    if(size==2){
        compare++;
        if(arr[0]>arr[1]) return arr[1];
        else return arr[0];
    }
    int mid = size/2;
    int left =  DivideAndConquerMin(arr,mid);
    compare++;
    int right = DivideAndConquerMin(arr+mid,size-mid);
    compare++;
    if(right>left) return left;
    else return right;
}
int main(){
    srand(time(0));
    vector<int>sizes = {1000,1500,2000,2500, 3000,3500,4000,4500};
    for(auto n : sizes){
        int arr[n];
        generator(arr,n);
        cout<<"Array length : "<<n<<"\n\n";
        {
            int a[n];
            copy(arr,arr+n,a);
            compare=0;
            DivideAndConquerMin(a,n);
            cout<<"Number of Comparisons in min : "<<compare<<endl;
        }
        {
            int a[n];
            copy(arr,arr+n,a);
            compare=0;
            DivideAndConquerMax(a,n);
            cout<<"Number of Comparisons in max : "<<compare<<endl;            
        }
        cout<<"\n\n"<<endl;
    }
}