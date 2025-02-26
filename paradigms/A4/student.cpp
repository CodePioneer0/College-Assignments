#include "student.h"
int main(){
    cout<<"Enter the number of students : ";
    int n;cin>>n;
    student arr[n];
    for(int i=0;i<n;i++){
        student s;
        s.ReadStudentData();
        arr[i] = s;
    }
    cout<<"\n\n";
    arr[0].displayNumOfStudent();
    for(int i=0;i<n;i++){
        arr[i].PrintStudentData();
    }
    cout<<endl;
}