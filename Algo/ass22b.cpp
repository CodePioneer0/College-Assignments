#include <iostream>
#include <vector>
#include <random>
#include <fstream>
using namespace std;

int compare_count = 0;
void generator(vector<int>&arr,int &n){
    for(int i=0;i<n;i++){
        arr[i] = rand()%10000+1; 
    }
}
pair<int,int> getMinAndSecondMin(vector<int>&arr,int &n,int low,int high){
    if(low==high){
        return {arr[low],INT_MAX};
    }
    if(high-low==1){
        compare_count++;
        if(arr[low]<arr[high]){
            return {arr[low],arr[high]};
        }
        else{
            return {arr[high],arr[low]};
        }
    }
    int mid = (low+high)>>1;
    auto left = getMinAndSecondMin(arr,n,low,mid);
    auto right = getMinAndSecondMin(arr,n,mid+1,high);

    int minElement,secondMin;
    compare_count+=2;
    if(left.first<right.first){
        minElement = left.first;
        secondMin = min(left.second,right.first);
    }
    else{
        minElement = right.first;
        secondMin = min(left.first,right.second);
    }

    return {minElement,secondMin};
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
           
            auto it = getMinAndSecondMin(a,n,0,n-1);
            cout<<"Minimum : "<<it.first<<" Second Minimum : "<<it.second<<endl;
            cout<<"Number of Comparisons in min and second min : "<<compare_count<<endl;
            csvFile << n << "," << compare_count << "\n";
        }
        cout<<"\n\n"<<endl;
    }
    csvFile.close();
}
