#include<iostream>
#include<string>
#include "student.h"
using namespace std;
int main(){
    cout<<"Enter the number of students: ";
    int n;cin>>n;
    student *arr = new student[n];
    cin.ignore();
    for(int i=0;i<n;i++){
        student s;
        s = ReadStudentData();
        arr[i] = s;
    }
    PrintStudentData(n,arr);
}