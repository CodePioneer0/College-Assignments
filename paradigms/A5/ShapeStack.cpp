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


const int StackSize = 10;
class ShapeStack{
    Shape *Stack[StackSize] = {nullptr};
    double TotalArea;
    int top;
public:
    ShapeStack() : TotalArea(0), top(0) {}
    bool push(){
        if(top == StackSize){
            cout<<"Stack Overflow"<<endl;
            return false;
        }
        int choice;
        cout<<"Enter 1 for Rectangle, 2 for Triangle, 3 for Circle : ";
        cin>>choice;
        switch(choice){
            case 1:
                Stack[top] = new Rectangle();
                Stack[top]->Read();
                TotalArea += Stack[top]->Area();
                break;
            case 2:
                Stack[top] = new Triangle();
                Stack[top]->Read();
                TotalArea += Stack[top]->Area();
                break;
            case 3:
                Stack[top] = new Circle();
                Stack[top]->Read();
                TotalArea += Stack[top]->Area();
                break;
            default:
                cout<<"Invalid choice"<<endl;
                return false;
        }
        top++;
        return true;
    }
    bool pop(){
        if(top == 0){
            cout<<"Stack Underflow"<<endl;
            return false;
        }
        top--;
        cout<<"Popped shape area: "<<Stack[top]->Area()<<endl;
        TotalArea -= Stack[top]->Area();
        delete Stack[top];
        Stack[top] = nullptr;
        return true;
    }
    void displayTotalArea() const {
        cout << "Total Area of all shapes in stack: " << TotalArea << endl;
    }
    void display(){
        for(int i=0;i<top;i++){
            cout<<"Shape "<<i+1<<": Area = "<<Stack[i]->Area()<<endl;
        }
    }
    
};
int main(){
    ShapeStack s;
    int choice;
    do{
        cout<<"1. Push\n2. Pop\n3. Display Total Area\n4. Display Shapes\n5. Exit\nEnter your choice: ";
        cin>>choice;
        switch(choice){
            case 1:
                s.push();
                break;
            case 2:
                s.pop();
                break;
            case 3:
                s.displayTotalArea();
                break;
            case 4:
                s.display();
                break;
            case 5:
                cout<<"Exiting..."<<endl;
                break;
            default:
                cout<<"Invalid choice"<<endl;
        }
    }while(choice != 5);
    return 0;
}
