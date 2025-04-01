#include<iostream>
#include<string>
using namespace std;

class Person{
protected:    
    string name;
    int age;
    string gender;
public:
    Person() : name(""),age(0),gender(""){}
    Person(const string &n,const int &a,const string &g) : name(n),age(a),gender(g){}
    void readData(){
        cout<<"Enter the name : ";
        cin>>name;
        cout<<"Enter the age : ";
        cin>>age;
        cout<<"Enter the gender : ";
        cin>>gender;
    }
    void writeData() const{
        cout<<"Name : "<<name<<endl;
        cout<<"Age : "<<age<<endl;
        cout<<"Gender :"<<gender<<endl;
    }
};

class Student : public Person{
private:    
    string dept;
    int year;
public:
    Student() : dept(""),year(0){}
    Student(const string &n,const int &a,const string &g,const string &d,const int &y) : Person(n,a,g),dept(d),year(y){} 
    void readData(){
        Person :: readData();
        cout<<"Enter the dept :"<<endl;
        cin>>dept;
        cout<<"Enter the year :"<<endl;
        cin>>year;
    }
    void writeData() const{
        cout<<"--Student Profile--"<<endl;
        Person::writeData();
        cout<<"Department : "<<dept<<endl;
        cout<<"Year : "<<year<<endl;
    }
};
class Clerk : public Person{
private:    
    int workLoad;
    double salary;
    public:
    Clerk() : workLoad(0),salary(0){}
    Clerk(const string &n,const int &a,const string &g,const int &w,const double &s) : Person(n,a,g), workLoad(w),salary(s){}
    void readData(){
        Person :: readData();
        cout<<"Enter the workload :";
        cin>>workLoad;
        cout<<"Enter the salary :";
        cin>>salary;
    }
    void writeData()const{
        cout<<"--Clerk Profile--"<<endl;
        Person::writeData();
        cout<<"Workload : "<<workLoad<<endl;
        cout<<"Salary : "<<salary<<endl;
    }

};

class Professor : public Person{
private:    
    string dept;
    int courseLoad;
    double salary;
public:
    Professor() : dept(""),courseLoad(0),salary(0){}
    Professor(const string &n,const int &a,const string &g,const string &d,const int &c,const double &s) : Person(n,a,g),dept(d),courseLoad(c),salary(s){}
    void readData(){
        Person :: readData();
        cout<<"Enter the department :";
        cin>>dept;
        cout<<"Enter the courseload :";
        cin>>courseLoad;
        cout<<"Enter the salary:";
        cin>>salary;
    }
    void writeData() const{
        cout<<"--Professor Profile--"<<endl;
        Person::writeData();
        cout<<"Department :"<<dept<<endl;
        cout<<"CourseLoad :"<<courseLoad<<endl;
        cout<<"Salary :"<<salary<<endl;
    }

};

int main(){
    Student student("John Smith", 20, "Male", "Computer Science", 2);
    Clerk clerk("Jane Doe", 35, "Female", 40, 45000.0);
    Professor professor("Dr. Robert Johnson", 45, "Male", "Physics", 12, 95000.0);
    student.writeData();
    clerk.writeData();
    professor.writeData();

}
