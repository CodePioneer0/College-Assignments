#include<iostream>
using namespace std;

template<typename T>
void insertionSort(T arr[], int n) {
    for(int i=1; i<n; i++) {
        int j = i;
        while(j>0 && arr[j-1]>arr[j]) {
            swap(arr[j-1], arr[j]);
            j--;
        }
    }
}

template<typename T>
void printArray(T arr[], int n) {
    for(int i=0; i<n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int choice;
    
    cout << "What type of array do you want to sort?\n";
    cout << "1. Integer Array\n";
    cout << "2. Float Array\n";
    cout << "3. Double Array\n";
    cout << "4. Short Array\n";
    cout << "Enter your choice: ";
    cin >> choice;
    
    if(choice == 1) {
        int n;
        cout << "Enter the number of integers: ";
        cin >> n;
        int* arr = new int[n];
        cout << "Enter " << n << " integers:\n";
        for(int i=0; i<n; i++) {
            cin >> arr[i];
        }
        
        cout << "Array before sorting: ";
        printArray(arr, n);
        
        insertionSort(arr, n);
        
        cout << "Array after sorting: ";
        printArray(arr, n);
        delete[] arr;
    }
    else if(choice == 2) {
        int n;
        cout << "Enter the number of floats: ";
        cin >> n;
        
        float* arr = new float[n];
        cout << "Enter " << n << " float numbers:\n";
        for(int i=0; i<n; i++) {
            cin >> arr[i];
        }
        
        cout << "Array before sorting: ";
        printArray(arr, n);
        insertionSort(arr, n);
        
        cout << "Array after sorting: ";
        printArray(arr, n);
        
        delete[] arr;
    }
    else if(choice == 3) {
        int n;
        cout << "Enter the number of doubles: ";
        cin >> n;
        
        double* arr = new double[n];
        cout << "Enter " << n << " double numbers:\n";
        for(int i=0; i<n; i++) {
            cin >> arr[i];
        }
        cout << "Array before sorting: ";
        printArray(arr, n);
        insertionSort(arr, n);
        cout << "Array after sorting: ";
        printArray(arr, n);
        delete[] arr;
    }
    else if(choice == 4) {
        int n;
        cout << "Enter the number of shorts: ";
        cin >> n;
        short* arr = new short[n];
        cout << "Enter " << n << " short numbers:\n";
        for(int i=0; i<n; i++) {
            cin >> arr[i];
        }
        
        cout << "Array before sorting: ";
        printArray(arr, n);
        
        insertionSort(arr, n);
        cout << "Array after sorting: ";
        printArray(arr, n);
        delete[] arr;
    }
    else {
        cout << "Invalid choice!" << endl;
    }
    
    return 0;
}