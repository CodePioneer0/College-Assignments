#include<iostream>
#include<random>
using namespace std;
#include<chrono>
using namespace std::chrono;
int exchanges = 0;

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
                                exchanges++;
                        }
                        else{
                                arr[j] = temp;
                                exchanges++;
                                break;
                        }
                }
                if(arr[0]>temp){
                        exchanges++;
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
                                exchanges++;
                                arr[j-1] = arr[j];
                        }
                        else{
                                exchanges++;
                                arr[j-1] = max;
                                max = arr[j];
                        }
                }
                exchanges++;
                arr[i] = max;
        }
}
void bubbleSortflagged(int arr[],int n){
        for(int i=n-1;i>0;i--){
                int max = arr[0];
                bool sorted = true;
                for(int j=0;j<=i;j++){
                        if(max>arr[j]){
                                exchanges++;
                                arr[j-1] = arr[j];
                                sorted = false;
                        }
                        else{
                                exchanges++;
                                arr[j-1] = max;
                                max = arr[j];
                        }
                }
                exchanges++;
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
                                exchanges++;
                                arr[j-1]=arr[j];
                                ind = j-1;
                        }
                        else{
                                exchanges++;
                                arr[j-1] = max;
                                max = arr[j];
                        }
                }
                exchanges++;
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
                       exchanges++;
                       temp[i]=arr[left];
                       left++;
                       i++; 
                }
                else{
                        exchanges++;
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
int median(int arr[], int low, int high) {
    int mid = (low + high)>>1;
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);
    return mid;
}
int partition(int arr[], int low, int high) {
    int pivotIndex = median(arr, low, high);
    int pivot = arr[pivotIndex];
    swap(arr[pivotIndex], arr[high]);
    int storeIndex = low;
    for (int i = low; i < high; i++) {
        if (arr[i] < pivot) {
            exchanges++;
            swap(arr[i], arr[storeIndex]);
            storeIndex++;
        }
    }
    exchanges++;
    swap(arr[storeIndex], arr[high]);
    return storeIndex;
}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
int avg(int sum,int n){
        return sum/n;
}
void generate(int arr[],int n){
        for(int i=0;i<n;i++){
                arr[i] = rand()%100000;
        }
}
int main(){
    int n = 10000;
    int arr[10000];
    {
        int a[10000];
        copy(arr,arr+n,a);
        generate(a,n);
        int sum = 0;
        for(int i=0;i<5;i++){
            auto start = high_resolution_clock::now();
            insertionSortNoSwap(a,n);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            sum+=duration.count();    
        }
        cout<<"Insertion Sort without Swaps: "<<avg(sum,5)<<" microseconds"<<endl;
    }
    {
        int a[10000];
        copy(arr,arr+n,a);
        int sum = 0;
        for(int i=0;i<5;i++){
            generate(a,n);
            auto start = high_resolution_clock::now();
            bubbleSortRangeLimited(a,n);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            sum+=duration.count();    
        }
        cout<<"Bubble sort range limited: "<<avg(sum,5)<<" microseconds"<<endl;
    }
    {
        int a[10000];
        copy(arr,arr+n,a);
        int sum = 0;
        for(int i=0;i<5;i++){
            generate(a,n);    
            auto start = high_resolution_clock::now();
            mergeSort(a,0,n-1);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            sum+=duration.count();    
        }
        cout<<"Merge Sort: "<<avg(sum,5)<<" microseconds"<<endl;
    }
    {
        int a[10000];
        copy(arr,arr+n,a);
        int sum = 0;
        for(int i=0;i<5;i++){
            generate(a,n);    
            auto start = high_resolution_clock::now();
            quickSort(a,0,n-1);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            sum+=duration.count();    
        }
        cout<<"Quick Sort: "<<avg(sum,5)<<" microseconds"<<endl;
    }
}