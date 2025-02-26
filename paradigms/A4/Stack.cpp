#include "intStack.h"

int main(){
    mystack s1(6);
    mystack s2(5);
    for(int i=1;i<=6;i++){
        s1.push(i);
    }
    for(int i=0;i<5;i++){
        s2.push(i+7);
    }
    cout<<"Stack 1: ";
    s1.display();
    cout<<"Stack 2: ";
    s2.display();
    mystack s3(11);
    int i=1;
    while(!s1.isEmpty() && !s2.isEmpty()){
        if(i%2==0){
            s3.push(s2.pop());
        }else{
            s3.push(s1.pop());
        }
        i++;
    }
    while(!s1.isEmpty()){
        s3.push(s1.pop());
    }
    while(!s2.isEmpty()){
        s3.push(s2.pop());
    }
    cout<<"Stack 3: ";
    s3.display();
    mystack s4 = s3;
    cout<<"Created using copy constructor\n";
    cout<<"Stack 4: ";
    s4.display();
    mystack s5(6);

    s5 = s3;
    cout<<"Created using assignment operator\n";
    cout<<"Stack 5: ";
    s5.display();
    mystack s6(6);
    for(int i=1;i<=10;i++){
        s6.push(i);
    }
    cout<<"Stack 6: ";
    s6.display();
    cout<<"Instance Count: "<<mystack::instCount()<<endl;
}