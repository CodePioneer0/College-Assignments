#include <iostream>
#include <cstring>
using namespace std;
class Vehicle {
    protected :
    int price;
    char *manufacturer;
    public :
    // Default constructor
    Vehicle(){
        price = 0;
        manufacturer = NULL;
    }
    ~Vehicle(){
        if(manufacturer != NULL){
            delete [] manufacturer;
        }
    }
    // Parameterized constructor
    Vehicle(const int &p, char *m){
        price = p;
        manufacturer = new char[strlen(m)+1];
        strcpy(manufacturer, m);
    }
    // Copy constructor
    Vehicle(const Vehicle &v){
        price = v.price;
        manufacturer = new char[strlen(v.manufacturer)+1];
        strcpy(manufacturer, v.manufacturer);
    }
    // Assignment operator
    Vehicle& operator=(const Vehicle &v){
        if(this == &v){
            return *this;
        }
        if(manufacturer != NULL){
            delete [] manufacturer;
        }
        price = v.price;
        manufacturer = new char[strlen(v.manufacturer)+1];
        strcpy(manufacturer, v.manufacturer);
        return *this;
    }
    // Read data
    void readData(){
        char m[100];
        cout << "Enter price: ";
        cin >> price;
        cout << "Enter manufacturer: ";
        cin >> m;
        manufacturer = new char[strlen(m)+1];
        strcpy(manufacturer, m);
    }
    // Display data
    void displayData() const{
        cout << "Price: " << price << endl;
        cout << "Manufacturer: " << manufacturer << endl;
    }
    
};

class Car : public Vehicle{
    private :    
    char *color;
    int NoOfSeats;
    char *model;
    public :
// Default constructor
   Car(){
       color = NULL;
       NoOfSeats = 0;
       model = NULL;
   }
   ~Car(){
         if(color != NULL){
              delete [] color;
         }
         if(model != NULL){
              delete [] model;
         }
   }
// Parameterized constructor
    Car(const int &p,char *m,char *c,const int &n,char *mo) : Vehicle(p,m){
        color = new char[strlen(c)+1];
        strcpy(color, c);
        NoOfSeats = n;
        model = new char[strlen(mo)+1];
        strcpy(model, mo);
    }
// Copy constructor
    Car(const Car &c) : Vehicle(c){
        color = new char[strlen(c.color)+1];
        strcpy(color, c.color);
        NoOfSeats = c.NoOfSeats;
        model = new char[strlen(c.model)+1];
        strcpy(model, c.model);
    }
// Assignment operator
    Car& operator=(const Car &c){
        if(this == &c){
            return *this;
        }
        Vehicle::operator=(c);
        if(color != NULL){
            delete [] color;
        }
        if(model != NULL){
            delete [] model;
        }
        color = new char[strlen(c.color)+1];
        strcpy(color, c.color);
        NoOfSeats = c.NoOfSeats;
        model = new char[strlen(c.model)+1];
        strcpy(model, c.model);
        return *this;
    }
// Read data
    void readData(){
        Vehicle::readData();
        char c[100], m[100];
        cout << "Enter color: ";
        cin >> c;
        cout << "Enter number of seats: ";
        cin >> NoOfSeats;
        cout << "Enter model: ";
        cin >> m;
        color = new char[strlen(c)+1];
        strcpy(color, c);
        model = new char[strlen(m)+1];
        strcpy(model, m);
    }
// Display data
    void displayData() const{
        cout << "--Car Profile--" << endl;
        Vehicle::displayData();
        cout << "Color: " << color << endl;
        cout << "Number of seats: " << NoOfSeats << endl;
        cout << "Model: " << model << endl;
    }
};
int main(){
    Vehicle v1;
    v1.readData();
    cout<<"--Vehicle Profile--"<<endl;
    v1.displayData();
    cout<<endl;
    cout<<"Made with copy constructor"<<endl;
    Vehicle v2 = v1; // Copy constructor
    v2.displayData();
    cout<<endl;
    cout<<"Made with assignment operator"<<endl;
    Vehicle v3;
    v3 = v1; // Assignment operator
    v3.displayData();



    Car c1;
    c1.readData();
    c1.displayData();
    cout<<endl;
    cout<<"Made with copy constructor"<<endl;
    Car c2 = c1; // Copy constructor
    c2.displayData();
    cout<<endl;
    cout<<"Made with assignment operator"<<endl;
    Car c3;
    c3 = c1; // Assignment operator
    c3.displayData();
    
    return 0;
}
