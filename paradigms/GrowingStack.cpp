#include<bits/stdc++.h>
using namespace std;
#define maxSize 100

vector<int> (){
    vector<int>v;
    return v;
}
void push(vector<int>&a,int &n){
    a.push_back(a);
}
void pop(vector<int>&a,int &top){
    top=a.pop_back();
}

int main(){

}