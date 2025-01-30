#include<iostream>
#include<vector>
#include<random>
#include <fstream>
using namespace std;
int compare_count = 0;
void generator(vector<int>&arr,int &n){
    for(int i=0;i<n;i++){
        arr[i] = rand()%10000+1; 
    }
}
void minAndSecondMin(vector<int>&arr,int &n,int &Min,int &sMin){
    if(n<2) {
        cout<<"Array length is less than 2\n";
        return;
    }
    Min = arr[0];
    sMin = arr[1];
    for(int i=1;i<n;i++){
        compare_count++;
        if(arr[i]<Min){
            sMin = Min;
            Min = arr[i];
        }
        else if(arr[i]<sMin){
            sMin = arr[i];
        }
    }
}
int main(){
    ofstream csvFile("compare_data.csv");
    csvFile << "ArraySize,Comparisons\n";
    vector<int>sizes = {1000,1500,2000,2500, 3000,3500,4000,4500,5000,5500,6000,6500,7000,7500,8000,8500,9000,9500,10000,11000,12000,13000,14000,15000};
    for(auto n : sizes){
        cout<<"Array length : "<<n<<"\n\n";
        {
            vector<int>a(n);
            generator(a,n);
            compare_count=0;
            int min,smin;
            minAndSecondMin(a,n,min,smin);
            cout<<"Minimum : "<<min<<" Second Minimum : "<<smin<<endl;
            cout<<"Number of Comparisons in min and second min : "<<compare_count<<endl;
            csvFile << n << "," << compare_count << "\n";
        }
        cout<<"\n\n"<<endl;
    }
    csvFile.close();
}