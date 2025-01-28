#include <iostream>
using namespace std;
#include "stack.h"
void stackEntry(mystack &st1,mystack &st2,mystack &st){
    if(isEmpty(st1) || isEmpty(st2)){
        cout<<"Stacks are initially empty!";
        return;
    }
    if(max(st1.size,st2.size)>100){
        cout<<"Stack can't be created due to insufficient space!"<<"\n";
        return;
    }
    
    int i = 1;
    int d = 0;
    while(!isEmpty(st1) && !isEmpty(st2)){
        if(i & 1){
            pop(st1,d);
            push(st,d);
        }
        else{
            pop(st2,d);
            push(st,d);
        }
        i++;
    }
    while(!isEmpty(st1)){
        pop(st1,d);
        push(st,d);
    }
    while(!isEmpty(st2)){
        pop(st2,d);
        push(st,d);
    }
}
int main() {
    mystack st1,st2;
    int size1;
    cout<<"Enter the size of the stack1: ";
    cin>>size1;
    int size2;
    cout<<"Enter the size of the stack2: ";
    cin>>size2;
    if (!initialize(st1, size1)) {
        printf("Failed to initialize the stack1\n");
        return 1;
    }
    if (!initialize(st2, size2)) {
        printf("Failed to initialize the stack2\n");
        return 1;
    }
    cout<<"Enter the elements of stack1: \n";
    for(int i=0;i<size1;i++){
        int d;
        cin>>d;
        push(st1,d);
    }
    cout<<"Enter the elements of stack2: \n";
    for(int i=0;i<size2;i++){
        int d;
        cin>>d;
        push(st2,d);
    }
    cout<<"Stack1: \n";
    printStack(st1);
    cout<<"Stack2: \n";
    printStack(st2);
    //Done with random stack creation
    mystack st;
    initialize(st,max(size1,size2));
    stackEntry(st1,st2,st);
    cout<<"After merging the stacks: ";
    printStack(st);

    delete[] st1.arr;
    delete[] st2.arr;
    return 0;
}
