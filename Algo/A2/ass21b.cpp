#include <iostream>
#include<vector>
#include<random>
#include <fstream>
using namespace std;
int compare_count = 0;
void generator(int arr[],int &n){
    for(int i=0;i<n;i++){
        arr[i] = rand()%10000+1; 
    }
}

int DivideAndConquerMax(int arr[], int size) {
    if(size==1) return arr[0];
    if(size==2){
        compare_count++;
        if(arr[0]>arr[1]) return arr[0];
        else return arr[1];
    }
    int mid = size/2;
    int left =  DivideAndConquerMax(arr,mid);
    int right = DivideAndConquerMax(arr+mid,size-mid);
    compare_count++;
    if(right>left) return right;
    else return left;
}
int DivideAndConquerMin(int arr[], int size) {
    if(size==1) return arr[0];
    if(size==2){
        compare_count++;
        if(arr[0]>arr[1]) return arr[1];
        else return arr[0];
    }
    int mid = size/2;
    int left =  DivideAndConquerMin(arr,mid);
    int right = DivideAndConquerMin(arr+mid,size-mid);
    compare_count++;
    if(right>left) return left;
    else return right;
}
int main(){
    ofstream csvFile("compare_data.csv");
    csvFile << "ArraySize,Comparisons\n";
    vector<int>sizes = {1000,1500,2000,2500, 3000,3500,4000,4500,5000,5500,6000,6500,7000,7500,8000,8500,9000,9500,10000,11000,12000,13000,14000,15000};
    for(auto n : sizes){
        int arr[n];
        generator(arr,n);
        cout<<"Array length : "<<n<<"\n\n";
        {
            int a[n];
            copy(arr,arr+n,a);
            compare_count=0;
            DivideAndConquerMax(a,n);
            DivideAndConquerMin(a,n);
            cout<<"Number of Comparisons in min and max : "<<compare_count<<endl;
            csvFile << n << "," << compare_count << "\n";
        }
        cout<<"\n\n"<<endl;
    }
    csvFile.close();
}