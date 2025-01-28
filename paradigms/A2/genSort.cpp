#include<iostream>
using namespace std;
template<typename T>
void insertionSort(T arr[],int n){
        for(int i=1;i<n;i++){
                int j = i;
                while(j>0 && arr[j-1]>arr[j]){
                        swap(arr[j-1],arr[j]);
                        j--;
                }
        }
}

int main(){
        float arr[] = {4.2,3.1,1.7,2.2,7.8};
        insertionSort(arr,5);
        for(int i=0;i<5;i++){
                cout<<arr[i]<<" ";
        }
}
