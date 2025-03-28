#include<iostream>
using namespace std;

class person{
    string name;
    int age;
    string gender;
    public:
    person() : name(""),age(0),gender(""){}
    person(string n,int a,string g) : name(n),age(a),gender(g){}
    void readData(){
        cout<<"Enter the name : ";
        cin>>name;
        cout<<"Enter the age : ";
        cin>>age;
        cout<<"Enter the gender : ";
        cin>>gender;
    }
    void writeData(){
        cout<<"Name : "<<name<<endl;
        cout<<"Age : "<<age<<endl;
        cout<<"Gender :"<<gender<<endl;
    }
};

class Student : public person{
    string dept;
    int year;
    public:
    Student() : dept(""),year(0){}
    Student(string n,int a,string g,string d,int y) : dept(d),year(y),person(n,a,g){} 
    void readData(){
        person :: readData();
        cout<<"Enter the dept :"<<endl;
        cin>>dept;
        cout<<"Enter the year :"<<endl;
        cin>>year;
    }
    void writeData(){
        person::writeData();
        cout<<"Department : "<<dept<<endl;
        cout<<"Year : "<<year<<endl;
    }
};
class Clerk : public person{
    int workLoad;
    int salary;
    public:
    Clerk() : workLoad(0),salary(0){}
    Clerk(string n,int a,string g,int w,int s) : workLoad(w),salary(s),person(n,a,g){}
    void readData(){
        person :: readData();
        cout<<"Enter the workload :"<<endl;
        cin>>workLoad;
        cout<<"Enter the salary :"<<endl;
        cin>>salary;
    }
    void writeData(){
        person::writeData();
        cout<<"Workload : "<<workLoad<<endl;
        cout<<"Salary : "<<salary<<endl;
    }

};

class Professor : public person{
    string dept;
    int courseLoad;
    int salary;
    Professor() : dept(""),courseLoad(0),(0){}
    Professor(string dept)
};

int main(){
    Student s("Sayak",21,"M","CST",2);
    s.writeData();
    Clerk C("Sayak",21,"M",12,1200000);
    C.writeData();

}
