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
int minElement(int arr[], int size) {
    int mini = 0;
    for (int i = 1; i < size; i++) {
        compare_count++;
        if (arr[i] < arr[mini]) {
            mini = i;
        }
    }
    return arr[mini];
}
int maxElement(int arr[], int size) {
    int maxi = 0;
    for (int i = 1; i < size; i++) {
        compare_count++;
        if (arr[i] > arr[maxi]) {
            maxi = i;
        }
    }
    return arr[maxi];
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
            minElement(a,n);
            maxElement(a,n);
            cout<<"Number of Comparisons in min and max : "<<compare_count<<endl;
            csvFile << n << "," << compare_count << "\n";
        }
        cout<<"\n\n"<<endl;
    }
    csvFile.close();
}

