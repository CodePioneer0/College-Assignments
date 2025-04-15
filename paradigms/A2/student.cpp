#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef struct student {
    string name;
    int age;
    string dept;
    int year;
} student;

student ReadStudentData() {
    student s;
    cout << "Name: ";
    getline(cin, s.name);
    cout << "Age: ";
    cin >> s.age;
    cin.ignore();
    cout << "Department: ";
    getline(cin, s.dept);
    cout << "Year: ";
    cin >> s.year;
    cin.ignore();
    return s;
}

student ReadStudentData(ifstream &file) {
    student s;
    getline(file, s.name);
    file >> s.age;
    file.ignore();
    getline(file, s.dept);
    file >> s.year;
    file.ignore();
    return s;
}

void PrintStudentData(const int &n, student *arr) {
    cout << "\nStudent Details:\n\n";
    for (int i = 0; i < n; i++) {
        cout << "Name: " << arr[i].name << endl;
        cout << "Age: " << arr[i].age << endl;
        cout << "Department: " << arr[i].dept << endl;
        cout << "Year: " << arr[i].year << endl;
    }
}

int main() {
    cout << "Do you want to read student data from a file? (yes/no): ";
    string choice;
    cin >> choice;
    cin.ignore();

    int n;
    student *arr;

    if (choice == "yes") {
        string filename;
        cout << "Enter filename: ";
        getline(cin, filename);
        ifstream file(filename);
        if (!file) {
            cout << "Error: Could not open the file.\n";
            return 1;
        }

        file >> n;
        file.ignore();
        arr = new student[n];
        for (int i = 0; i < n; i++) {
            arr[i] = ReadStudentData(file);
        }
        file.close();
    } else {
        cout << "Enter the number of students: ";
        cin >> n;
        cin.ignore();
        arr = new student[n];
        for (int i = 0; i < n; i++) {
            arr[i] = ReadStudentData();
        }
    }

    PrintStudentData(n, arr);

    delete[] arr;
    return 0;
}
