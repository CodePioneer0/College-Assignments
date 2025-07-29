#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int regions = 4;
const int salesman = 6;
const int products = 8;

const int productPrice[products][2] = {
    { 1, 100 }, { 2, 200 }, { 3, 300 }, { 4, 400 },
    { 5, 500 }, { 6, 600 }, { 7, 700 }, { 8, 800 }
};
void generatedata(){
    srand(time(0));
    ofstream outfile("sales.txt");
    for(int i=1;i<=1000;i++){
        int regionNo = rand() % regions + 1;
        int personNo = rand() % salesman + 1;
        int productCode = rand() % products + 1;
        int quantity = rand() % 10 + 1;
        outfile << regionNo << " " << personNo << " " << productCode << " " << quantity << endl;
    }
    outfile.close();
    cout << "Data generated in sales.txt" << endl;
}
int main(){
    generatedata();
    int sales[regions][salesman] = {0};
    ifstream inFile("sales.txt");
    if (!inFile) {
        cerr << "Error opening file." << endl;
        return 1;
    }
    int regionNo, personNo, productCode, quantity;
    while(inFile>>regionNo>>personNo>>productCode>>quantity) {
        int unitPrice = 0;
        for(int i=0;i<products;i++){
            if(productCode == productPrice[i][0]){
                unitPrice = productPrice[i][1];
                break;
            }
        }
        int amount = unitPrice * quantity;
        if(regionNo>=1 && regionNo<=4 && personNo>=1 && personNo<=6){
            sales[regionNo-1][personNo-1] += amount;
        }
    }
    inFile.close();

    ofstream outfile("output.txt");
    if(!outfile){
        cout<<"Error Opening Output file!"<<endl;
        return 1;
    }
    outfile<<"ABC Company"<<endl;

    for(int i = 0;i<regions;i++){
        int regionTotal = 0;
        outfile<<"Region "<<(i + 1)<<endl; 
        for(int j=0;j<salesman;j++){
            outfile<<"Salesman "<<(j+1)<<" Rs. " << sales[i][j]<<"/-"<<endl;
            regionTotal+=sales[i][j];
        }
        outfile<<"Total sale at Region "<<(i+1) <<" Rs. "<<regionTotal<<"/-"<<endl;
    }
    outfile.close();
    return 0;
}
