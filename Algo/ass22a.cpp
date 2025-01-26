#include<iostream>
#include<vector>
#include<random>
using namespace std;
int compare_count = 0;
void generator(int arr[],int &n){
    for(int i=0;i<n;i++){
        arr[i] = rand()%10000+1; 
    }
}
vector<int> minAndSecondMin(){
    
}