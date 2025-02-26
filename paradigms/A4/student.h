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