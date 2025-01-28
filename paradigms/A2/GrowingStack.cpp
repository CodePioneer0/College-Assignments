#include<iostream>
using namespace std;    
#include "stack.h"

int main(){
    mystack st;
    int n;
    cout<<"Enter the size of the stack: ";
    cin>>n;
    if(!initialize(st,n)){
        cout<<"Failed to initialize the stack\n";
        return 1;
    }
    cout<<"1.push\n2.pop\n3.isEmpty\n4.isFull\n5.currentSize\n6.getMaxSize\n7.printStack\n8.exit\n";
    int ch;
    int d;
    while(1){
        cout<<"Enter your choice: ";
        cin>>ch;
        switch(ch){
            case 1:
                cout<<"Enter the element to push: ";
                cin>>d;
                if(push(st,d)){
                    cout<<"Element pushed successfully\n";
                }
                else{
                    cout<<"Failed to push the element\n";
                }
                break;
            case 2:
                if(pop(st,d)){
                    cout<<"Element popped successfully: "<<d<<"\n";
                }
                else{
                    cout<<"Failed to pop the element\n";
                }
                break;
            case 3:
                if(isEmpty(st)){
                    cout<<"Stack is empty\n";
                }
                else{
                    cout<<"Stack is not empty\n";
                }
                break;
            case 4:
                if(isFull(st)){
                    cout<<"Stack is full\n";
                }
                else{
                    cout<<"Stack is not full\n";
                }
                break;
            case 5:
                cout<<"Current size of the stack: "<<currentSize(st)<<"\n";
                break;
            case 6:
                cout<<"Maximum size of the stack: "<<getMaxSize()<<"\n";
                break;
            case 7:
                printStack(st);
                break;
            case 8:
                return 0;
            default:
                cout<<"Invalid choice\n";
        }
    }
}