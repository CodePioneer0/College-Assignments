#include<iostream>
using namespace std;

class Shape{
    public:
    virtual void Read() = 0;
    virtual double Area() = 0;
};

class Rectangle : public Shape{
    double length;
    double breadth;
    public:
    void Read(){
        cout<<"Enter the length of Rectangle :";
        cin>>length;
        cout<<"Enter the breadth of Rectangle :";
        cin>>breadth;
    }
    double Area(){
        return length*breadth;
    }
};

class Triangle : public Shape{
    double base;
    double height;
    public:
    void Read(){
        cout<<"Enter the base of Triangle :";
        cin>>base;
        cout<<"Enter the height of Triangle :";
        cin>>height;
    }
    double Area(){
        return 0.5*base*height;
    }
};
class Circle : public Shape{
    double radius;
    public:
    void Read(){
        cout<<"Enter the radius of Circle :";
        cin>>radius;
    }
    double Area(){
        return 3.14*radius*radius;
    }
};

int main(){
    double area = 0;
    Shape *s[3];
    s[0] = new Rectangle();
    s[1] = new Triangle();
    s[2] = new Circle();
    for(int i=0;i<3;i++){
        s[i]->Read();
    }
    for(int i=0;i<3;i++){
        area += s[i]->Area();
    }
    cout<<"Total Area = "<<area<<endl;
    for(int i=0;i<3;i++){
        delete s[i];
    }
    return 0;
}
