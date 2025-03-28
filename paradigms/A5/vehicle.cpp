#include <iostream>
using namespace std;
Class Vehicle {
    private :
    int price;
    char *manufacturer;
    public :
    // Default constructor
    Vehicle(){
        price = 0;
        manufacturer = NULL;
    }
    // Parameterized constructor
    Vehicle(int p, char *m){
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
        cout << "Enter price: ";
        cin >> price;
        cout << "Enter manufacturer: ";
        cin >> manufacturer;
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
// Parameterized constructor
    Car(int p,char *m,char *c,int n,char *mo) : Vehicle(p,m){
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
        color = new char[strlen(c.color)+1];
        strcpy(color, c.color);
        NoOfSeats = c.NoOfSeats;
        if(model != NULL){
            delete [] model;
        }
        model = new char[strlen(c.model)+1];
        strcpy(model, c.model);
        return *this;
    }
// Read data
    void readData(){
        Vehicle::readData();
        cout << "Enter color: ";
        cin >> color;
        cout << "Enter number of seats: ";
        cin >> NoOfSeats;
        cout << "Enter model: ";
        cin >> model;
    }
// Display data
    void displayData() const{
        Vehicle::displayData();
        cout << "Color: " << color << endl;
        cout << "Number of seats: " << NoOfSeats << endl;
        cout << "Model: " << model << endl;
    }
}
