#include <iostream>
#include <vector>
#include <random>
#include <fstream>
using namespace std;
void generator(vector<int>&arr,int &n){
    for(int i=0;i<n;i++){
        arr[i] = rand()%10000+1; 
    }
}
int compare_count = 0;

int main() {
    
    ofstream csvFile("compare_data.csv");
    csvFile << "ArraySize,Comparisons\n";
    vector<int>sizes = {1000,1500,2000,2500, 3000,3500,4000,4500,5000,5500,6000,6500,7000,7500,8000,8500,9000,9500,10000,11000,12000,13000,14000,15000};
    for(auto n : sizes){
        cout<<"Array length : "<<n<<"\n\n";
        {
            vector<int>arr(n);
            generator(arr,n);
            compare_count=0;
           
            vector<pair<int,vector<int>>> game;
            for(int i=0;i<n;i++){
                game.push_back({arr[i],{}});
            }

            while(game.size()>1){
                vector<pair<int,vector<int>>>nextRound;
                for(int i=0;i<game.size()-1;i+=2){
                    auto a = game[i];
                    auto b = game[i+1];
                    compare_count++;   
                    if(a.first<b.first){
                        a.second.push_back(b.first);
                        nextRound.push_back(a);
                    }
                    else{
                        b.second.push_back(a.first);
                        nextRound.push_back(b);
                    }
                }
                if(game.size() & 1){
                    nextRound.push_back(game.back());
                }
                game = nextRound;
            }
            int minElement = game[0].first;
            int secondMin = INT_MAX;
            auto remaining = game[0].second;
            for(auto it : remaining){
                compare_count++;
                secondMin = min(secondMin,it);   
            }
            cout<<minElement<<" "<<secondMin<<endl;
            csvFile << n << "," << compare_count << "\n";
        }
        cout<<"\n\n"<<endl;
    }
    csvFile.close();
    return 0;
}