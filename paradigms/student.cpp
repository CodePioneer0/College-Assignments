#include<bits/stdc++.h>
using namespace std;
typedef struct student{
    string name;
    int age;
    string dept;
    int year;
}student;
student ReadStudentData(){
    student s;
    cout<<"Name : ";
    getline(cin,s.name);
    cout<<"Roll : ";
    cin>>s.age;
    cin.ignore();
    cout<<"Department :";
    getline(cin,s.dept);
    cout<<"Year :";
    cin>>s.year;
    cin.ignore();
    return s;
}
void PrintStudentData(int n,student *&arr){
    cout<<"Student Details :\n\n";
    for(int i=0;i<n;i++){
        cout<<"Name : "<<arr[i].name<<endl;
        cout<<"Age : "<<arr[i].age<<endl;
        cout<<"Department : "<<arr[i].dept<<endl;
        cout<<"Year : "<<arr[i].year<<endl;
    }
    
}
int main(){
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