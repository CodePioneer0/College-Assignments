#include <iostream>
#include <vector>
#include <random>
#include <fstream>
using namespace std;

void generator(vector<int>& arr, int n) {
   for (int i = 0; i < n; i++) {
      arr[i] = rand() % 10000 + 1;
   }
}

int compare_count = 0;

int tournamentMethod(vector<int>& arr, int low, int high, vector<int>& losers) {
    if (low == high) {
        return arr[low];
    }
    
    int mid = (low + high) >> 1;
    int left = tournamentMethod(arr, low, mid, losers);
    int right = tournamentMethod(arr, mid + 1, high, losers);
    
    compare_count++;
    if (left < right) {
        losers.push_back(right);
        return left;
    } else {
        losers.push_back(left);
        return right;
    }
}

int main() {
    srand(time(0));
    ofstream csvFile("compare_data.csv");
    csvFile << "ArraySize,Comparisons\n";
    
    vector<int> sizes = {1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500,
                         6000, 6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000, 11000,
                         12000, 13000, 14000, 15000};
    
    for (auto n : sizes) {
        cout << "Array length: " << n << "\n\n";
        
        vector<int> arr(n);
        generator(arr, n);
        compare_count = 0;
        vector<int> losers;
        
        int minElement = tournamentMethod(arr, 0, n - 1, losers);
        
        cout << "Minimum element: " << minElement << endl;


        int secondMinElement = losers[0];
        for (int i = 1; i < losers.size(); i++) {
            
            if (losers[i] < secondMinElement) {
                compare_count++;
                secondMinElement = losers[i];
            }
        }

        cout << "Second Minimum element: " << secondMinElement << endl;
        cout << "Comparisons: " << compare_count << endl;
        csvFile << n << "," << compare_count << "\n";
        
        cout << "\n\n";
    }
    
    csvFile.close();
    return 0;
}
