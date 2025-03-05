#include<iostream>
using namespace std;

class ComplexNumber {
    int real;
    int imag;
    public:
    ComplexNumber(int r=0, int i=0){
        real = r;
        imag = i;
    }
    void display() const{
        cout<<real<<" + "<<imag<<"i\n";
    }
    const ComplexNumber operator+(const ComplexNumber &c) const{
        ComplexNumber temp;
        temp.real = real + c.real;
        temp.imag = imag + c.imag;
        return temp;
    }
    friend const ComplexNumber operator+(const ComplexNumber&, const ComplexNumber&);
    friend const ComplexNumber operator-(const ComplexNumber &, const ComplexNumber &);
};
const ComplexNumber operator+(const ComplexNumber &c1, const ComplexNumber &c2){
    ComplexNumber temp;
    temp.real = c1.real + c2.real;
    temp.imag = c1.imag + c2.imag;
    return temp;
}
const ComplexNumber operator-(const ComplexNumber &c1, const ComplexNumber &c2){
    ComplexNumber temp;
    temp.real = c1.real - c2.real;
    temp.imag = c1.imag - c2.imag;
    return temp;
}


int main(){
    ComplexNumber c1(2,3), c2(4,5), c3;
    c3.display();
    c1.display();
    c2.display();
    c3 = 10 - c2;
    c3.display();
    return 0;
}