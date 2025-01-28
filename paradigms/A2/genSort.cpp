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

