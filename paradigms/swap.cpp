#include<bits/stdc++.h>
using namespace std;

template<typename T>
void swapElem(T &a,T &b){
    T temp = a;
    a = b;
    b = temp;
}

typedef struct shibpur{
    int data;
}shibpur;

int main(){
    shibpur main;
    shibpur saltlake;
    main.data = 1;
    saltlake.data = 2;
    swapElem(main,saltlake);
    cout<<main.data<<" "<<saltlake.data<<endl;
}