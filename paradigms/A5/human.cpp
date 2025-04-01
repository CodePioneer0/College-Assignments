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

class academician : virtual public Person{
protected:
    string dept;
public:
    academician() : Person(),dept(""){}
    academician(const string &n,const int &a,const string &g,const string &d) : Person(n,a,g),dept(d){}
    void readData(){
        Person::readData();
        cout<<"Enter the department : ";
        cin>>dept;
    }
    void writeData() const{
        Person::writeData();
        cout<<"Department : "<<dept<<endl;
    }
};

class Employee : virtual public Person{
protected:
    double salary;
public:
    Employee() : Person(),salary(0){}
    Employee(const string &n,const int &a,const string &g,const double &s) : Person(n,a,g),salary(s){}
    void readData(){
        Person::readData();
        cout<<"Enter the salary : ";
        cin>>salary;
    }
    void writeData() const{
        Person::writeData();
        cout<<"Salary : "<<salary<<endl;
    }
};
class Student : public academician{
private:
    int year;
public:
    Student() : Person(),academician(),year(0){}
    Student(const string &n,const int &a,const string &g,const string &d,const int &y) : Person(n,a,g) ,academician(n,a,g,d),year(y){}
    void readData(){
        academician::readData();
        cout<<"Enter the year of study : ";
        cin>>year;
    }
    void writeData() const{
        academician::writeData();
        cout<<"Year of study : "<<year<<endl;
    }
};

class clerk : public Employee{
private:
    int WorkLoad;
public:
    clerk() : Person(),Employee(),WorkLoad(0){}
    clerk(const string &n,const int &a,const string &g,const double &s,const int &w) : Person(n,a,g),Employee(n,a,g,s),WorkLoad(w){}
    void readData(){
        Employee::readData();
        cout<<"Enter the work load : ";
        cin>>WorkLoad;
    }
    void writeData() const{
        Employee::writeData();
        cout<<"Work load : "<<WorkLoad<<endl;
    }
};
class Professor : public academician, public Employee{
private:
    int CourseLoad;
public:
    Professor() : Person(), academician(),Employee(),CourseLoad(0){}
    Professor(const string &n,const int &a,const string &g,const string &d,const double &s,const int &c) : Person(n,a,g),academician(n,a,g,d),Employee(n,a,g,s),CourseLoad(c){}
    void readData(){
        Person::readData();
        cout<<"Enter the department : ";
        cin>>dept;
        cout<<"Enter the salary : ";
        cin>>salary;
        cout<<"Enter the course load : ";
        cin>>CourseLoad;
    }
    void writeData() const{
        Person::writeData();
        cout<<"Department : "<<dept<<endl;
        cout<<"Salary : "<<salary<<endl;
        cout<<"Course load : "<<CourseLoad<<endl;
    }
};

int main(){
    // Student s;
    // cout<<"Enter the details of student : "<<endl;
    // s.readData();
    // cout<<endl<<"Student Details : "<<endl;
    // s.writeData();
    // cout<<endl;
    // cout<<"Enter the details of clerk : "<<endl;
    // clerk c;
    // c.readData();
    // cout<<endl<<"Clerk Details : "<<endl;
    // c.writeData();
    // cout<<endl;
    // cout<<"Enter the details of professor : "<<endl;    
    // Professor p;
    // p.readData();
    // cout<<endl<<"Professor Details : "<<endl;
    // p.writeData();
    // cout<<endl;
    Student s("Sayak",21,"M","CS",2);
    cout<<endl<<"Student Details : "<<endl;
    s.writeData();
    cout<<endl;
    clerk c("Sayak",21,"M",10000,5);
    cout<<endl<<"Clerk Details : "<<endl;
    c.writeData();
    cout<<endl;
    Professor p("Sayak",21,"M","CS",10000,5);
    cout<<endl<<"Professor Details : "<<endl;
    p.writeData();
    cout<<endl;
    return 0;
}
