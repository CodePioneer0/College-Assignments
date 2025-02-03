#include "GenericSort.h"
template<typename T>
void printArray(T arr[],int n){
        for(int i=0;i<n;i++){
                cout<<arr[i]<<" ";
        }
}
struct Student{
        string name;
        int age;
};
int main(){
        int arr[] = {5,4,3,2,1};
        float arr1[] = {5.5,4.4,3.3,2.2,1.1};
        double arr2[] = {5.5,4.4,3.3,2.2,1.1};
        short arr3[] = {5,4,3,2,1};
        struct Student s[2];
        s[0].name = "A";
        s[0].age = 20;
        s[1].name = "B";
        s[1].age = 21;
        insertionSort(arr,5);
        insertionSort(arr1,5);
        insertionSort(arr2,5);
        insertionSort(arr3,5);
        //insertionSort(s,2);
        cout<<"Integers: ";
        printArray(arr,5);
        cout<<endl;
        cout<<"Floats: ";
        printArray(arr1,5);
        cout<<endl;
        cout<<"Doubles: ";
        printArray(arr2,5);
        cout<<endl;
        cout<<"Shorts: ";
        printArray(arr3,5);
        cout<<endl;

}
