#include<iostream>
using namespace std;
class student{
private:    
    string name;
    int age;
    string dept;
    int year;
    static int studentCount;
public:
    student(){
        cout<<"Constructor is Called\n";
        studentCount++;
    }
    ~student(){
        cout<<"Destructor is Called\n";
        studentCount--;
    }
    static void displayNumOfStudent();
    void ReadStudentData();
    void PrintStudentData() const;
};
void student :: ReadStudentData(){
    cout<<"Enter name : ";
    cin>>this->name;
    cout<<"Enter age : ";
    cin>>this->age;
    cout<<"Enter department : ";
    cin>>this->dept;
    cout<<"Enter the year : ";
    cin>>this->year;
    cout<<"\n";
}

void student :: PrintStudentData() const{
    cout<<"Name : "<<this->name<<"\n";
    cout<<"Age  : "<<this->age<<"\n";
    cout<<"Department : "<<this->dept<<"\n";
    cout<<"Year : "<<this->year<<"\n"; 
}

int student :: studentCount = 0;
void student::displayNumOfStudent(){
    cout<<"Number of students : "<<studentCount<<endl;
}
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