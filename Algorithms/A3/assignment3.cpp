#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

int normalComparisons = 0;
int medianComparisons = 0;


void generator(int arr[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}


void quickSort(int arr[], int low, int high) {
    if (low >= high) return;

    int pivot = arr[low], left = low, right = high;

    while (left < right) {
        while (left < high && arr[left] <= pivot) {
            left++;
            normalComparisons++;
        }
        while (right > low && arr[right] > pivot) {
            right--;
            normalComparisons++;
        }
        if (left < right) {
            swap(arr[left], arr[right]);
        }
    }

    swap(arr[low], arr[right]);
    quickSort(arr, low, right - 1);
    quickSort(arr, right + 1, high);
}


int findRank(int r, int arr[], int n) {
    if (n <= 5) {
        sort(arr, arr + n);
        return arr[r];
    }

    int size = (n + 4) / 5;
    int *MedianArr = new int[size];

    for (int i = 0; i < size; i++) {
        int start = i * 5;
        int groupLen = min(5, n - start);
        sort(arr + start, arr + start + groupLen);
        MedianArr[i] = arr[start + groupLen / 2];
    }

    int x = findRank(size / 2, MedianArr, size);
    delete[] MedianArr;

    int *AL = new int[n];
    int *AR = new int[n];
    int low = 0, high = 0, equal = 0;

    for (int i = 0; i < n; i++) {
        medianComparisons++;
        if (arr[i] < x) {
            AL[low++] = arr[i];
        } else if (arr[i] > x) {
            AR[high++] = arr[i];
        } else {
            equal++;
        }
    }

    if (r < low) {
        int res = findRank(r, AL, low);
        delete[] AL;
        delete[] AR;
        return res;
    } else if (r >= low + equal) {
        int res = findRank(r - low - equal, AR, high);
        delete[] AL;
        delete[] AR;
        return res;
    } else {
        delete[] AL;
        delete[] AR;
        return x;
    }
}

void quickSortMedianPivot(int arr[], int low, int high) {
    if (low >= high) return;

    int size = high - low + 1;
    int pivotValue = findRank(size / 2, arr + low, size);

    int pivotIndex = low;
    for (int i = low; i <= high; i++) {
        if (arr[i] == pivotValue) {
            pivotIndex = i;
            break;
        }
    }
    swap(arr[low], arr[pivotIndex]);

    int left = low, right = high;
    while (left < right) {
        while (left < high && arr[left] <= pivotValue) {
            left++;
            medianComparisons++;
        }
        while (right > low && arr[right] > pivotValue) {
            right--;
            medianComparisons++;
        }
        if (left < right) {
            swap(arr[left], arr[right]);
        }
    }

    swap(arr[low], arr[right]);
    quickSortMedianPivot(arr, low, right - 1);
    quickSortMedianPivot(arr, right + 1, high);
}


int main() {
    srand((unsigned)time(NULL));
    ofstream file("comparisons.csv");
    file << "ArraySize,NormalQS,MedianPivotQS\n";
    vector<int> sizes = {1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};
    for (int size : sizes) {
        int *arr = new int[size];
        generator(arr, size);
        normalComparisons = 0;
        medianComparisons = 0;

        {
            int *a = new int[size];
            copy(arr, arr + size, a);
            quickSort(a, 0, size - 1);
            delete[] a;
        }
        {
            int *a = new int[size];
            copy(arr, arr + size, a);
            quickSortMedianPivot(a, 0, size - 1);
            delete[] a;
        }

        file << size << "," << normalComparisons << "," << medianComparisons << "\n";
        delete[] arr;
    }

    file.close();
    cout << "Comparison results saved in comparisons.csv\n";
    return 0;
}
