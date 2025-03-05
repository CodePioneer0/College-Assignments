#include<iostream>
using namespace std;

class student {
private:
    string name;
    int age;
    string dept;
    int year;
    static int studentCount;
    static student* freeList;

public:
    student() {
        cout << "Constructor is Called\n";
        studentCount++;
    }
    ~student() {
        cout << "Destructor is Called\n";
        studentCount--;
    }

    static void* operator new(size_t size) {
        if (freeList) {
            student* obj = freeList;
            freeList = freeList->freeList;
            return static_cast<void*>(obj);
        }
        return ::operator new(size);
    }

    static void operator delete(void* ptr) {
        student* obj = static_cast<student*>(ptr);
        obj->freeList = freeList;
        freeList = obj;
    }

    static void displayNumOfStudent();
    void ReadStudentData();
    void PrintStudentData() const;
};



void student::ReadStudentData() {
    cout << "Enter name : ";
    cin >> name;
    cout << "Enter age : ";
    cin >> age;
    cout << "Enter department : ";
    cin >> dept;
    cout << "Enter the year : ";
    cin >> year;
    cout << "\n";
}

void student::PrintStudentData() const {
    cout << "Name : " << name << "\n";
    cout << "Age  : " << age << "\n";
    cout << "Department : " << dept << "\n";
    cout << "Year : " << year << "\n"; 
}

void student::displayNumOfStudent() {
    cout << "Number of students : " << studentCount << endl;
}

student* student::freeList = nullptr;
int student::studentCount = 0;

int main() {
    student* s1 = new student();
    // s1->ReadStudentData();
    // s1->PrintStudentData();
    // delete s1;
    
    // student* s2 = new student();
    // s2->ReadStudentData();
    // s2->PrintStudentData();
    // delete s2;
    
    return 0;
}