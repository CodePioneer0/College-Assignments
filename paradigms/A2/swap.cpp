#include<bits/stdc++.h>
using namespace std;

template<typename T>
void swapElem(T &a,T &b){
    T temp = a;
    a = b;
    b = temp;
}
struct MyStruct {
    int x;
    double y;
};

int main() {
    int a = 1, b = 2;
    swapElem(a, b);
    cout<<a<<" "<<b<<endl;

    short sa = 3, sb = 4;
    swapElem(sa, sb);
    cout<<sa<<" "<<sb<<endl;

    float fa = 1.5f, fb = 2.5f;
    swapElem(fa, fb);
    cout<<fa<<" "<<fb<<endl;

    double da = 10.25, db = 20.75;
    swapElem(da, db);
    cout<<da<<" "<<db<<endl;

    MyStruct s1 {10, 3.14}, s2 {20, 6.28};
    swapElem(s1, s2);
    cout<<s1.x<<" "<<s1.y<<endl;

    return 0;
}
