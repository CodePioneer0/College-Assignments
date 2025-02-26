#include "GenStack.h"
int main(){
    mystack<int>s1(3);
    s1.push(1);
    s1.push(2);
    s1.push(3);
    cout<<"Interger Stack\n";
    s1.display();
    mystack<double>s2(3);
    s2.push(1.1);
    s2.push(2.2);
    s2.push(3.3);
    cout<<"Double Stack\n";
    s2.display();
   mystack<short>s3(3);
    s3.push(1);
    s3.push(2);
    s3.push(3);
    cout<<"Short Stack\n";
    s3.display();
    mystack<float>s4(3);
    s4.push(1.1);
    s4.push(2.2);
    s4.push(3.3);
    cout<<"Float Stack\n";
    s4.display();
    mystruct ms1,ms2,ms3;
    ms1.a = 1;
    ms2.a = 2;
    ms3.a = 3;
    mystack<mystruct>s5(3);
    s5.push(ms1);
    s5.push(ms2);
    s5.push(ms3);
    cout<<"Struct Stack\n";
    s5.display();
    cout<<"Number of instances: "<<s1.instCount()<<endl;
    return 0;
}
