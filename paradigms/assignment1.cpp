#include<bits/stdc++.h>
using namespace std;


void insertionSort(int arr[],int n){
        for(int i=1;i<n;i++){
                int j = i;
                while(j>0 && arr[j-1]>arr[j]){
                        swap(arr[j-1],arr[j]);
                        j--;
                }
        }
}
void insertionSortNoSwap(int arr[],int n){
        for(int i = 1;i<n;i++){
                int temp = arr[i];
                for(int j=i;j>0;j--){
                        if(arr[j-1]>temp){
                                arr[j] = arr[j-1];
                        }
                        else{
                                arr[j] = temp;
                                break;
                        }
                }
                if(arr[0]>temp){
                        arr[0]=temp;
                }
        }



}
void bubbleSort(int arr[],int n){
        for(int i=n-1;i>0;i--){
                for(int j=0;j<=i-1;j++){
                        if(arr[j]>arr[j+1]){
                                swap(arr[j],arr[j+1]);
                        }
                }
        }
}
void bubbleSortNoSwap(int arr[],int n){
        for(int i=n-1;i>0;i--){
                int max = arr[0];
                for(int j=0;j<=i;j++){
                        if(max>arr[j]){
                                arr[j-1] = arr[j];
                        }
                        else{
                                arr[j-1] = max;
                                max = arr[j];
                        }
                }
                arr[i] = max;
        }
}
void bubbleSortflagged(int arr[],int n){
        for(int i=n-1;i>0;i--){
                int max = arr[0];
                bool sorted = true;
                for(int j=0;j<=i;j++){
                        if(max>arr[j]){
                                arr[j-1] = arr[j];
                                sorted = false;
                        }
                        else{
                                arr[j-1] = max;
                                max = arr[j];
                        }
                }
                arr[i] = max;
                if(sorted) break;
        }
}
void bubbleSortRangeLimited(int arr[],int &n){
        for(int i=n-1;i>0;){
                int max = arr[0];
                int ind = 0;
                for(int j=1;j<i;j++){
                        if(max>arr[j]){
                                arr[j-1]=arr[j];
                                ind = j-1;
                        }
                        else{
                                arr[j-1] = max;
                                max = arr[j];
                        }
                }
                arr[i] = max;
                i=ind;
        }
}
void merge(int arr[],int low,int mid,int high){
        int left = low;
        int right = mid+1;
        int temp[high-low+1];
        int i = 0;
        while(left<=mid && right<=high){
                if(arr[left]<=arr[right]){
                       temp[i]=arr[left];
                       left++;
                       i++; 
                }
                else{
                        temp[i]=arr[right];
                        right++;
                        i++;
                }
        }
        while(left<=mid){
                temp[i]=arr[left];
                left++;
                i++; 
        }
        while(right<=high){
                temp[i]=arr[right];
                right++;
                i++; 
        }
        for(int j=low;j<=high;j++){
                arr[j] = temp[j-low];
        }
}
void mergeSort(int arr[],int low,int high){
        if(low>=high) return;
        int mid = (low+high)>>1;
        mergeSort(arr,low,mid);
        mergeSort(arr,mid+1,high);
        merge(arr,low,mid,high);
}

int main(){
        int n = 20;
        int a[20]={1 ,16, 12, 26 ,25 ,35 ,33, 58 ,45, 42, 56, 67, 83, 75, 74, 86, 81, 88, 99, 95};
        int b[20] = {1 ,17, 21, 42, 24, 27, 32, 35, 45, 47, 57, 23, 66, 69, 70, 76, 87, 85, 95, 99};
        int c[20]={22 ,20 ,81 ,38, 95, 84, 99, 12, 79, 44, 26, 87, 96, 10, 48, 80, 1, 31, 16, 92};
        mergeSort(a,0,19);
        for(int i=0;i<n;i++){
                cout<<a[i]<<' ';
        }
        cout<<"\n";
}