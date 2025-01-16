#include<bits/stdc++.h>
#include <chrono>
using namespace std::chrono;
using namespace std;


int swap_count = 0;
int compare_count = 0;

void generator(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000 + 1;
    }
}

void bubbleSort(int arr[], int n) {
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j <= i - 1; j++) {
            compare_count+=2;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swap_count++;
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            swap(arr[j + 1], arr[j]);
            j--;
            swap_count++;
            compare_count++;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int mini = i;
        for (int j = i + 1; j < n; j++) {
            compare_count++;
            if (arr[j] < arr[mini]) {
                mini = j;
            }
        }
        swap(arr[mini], arr[i]);
        swap_count++;
    }
}

void mergeFunc(int arr[], int low, int mid, int high) {
    int left = low;
    int right = mid + 1;
    int temp[high - low + 1];
    int i = 0;

    while (left <= mid && right <= high) { 
        swap_count++;        
        if (arr[left] <= arr[right]) {
            compare_count++;
            temp[i++] = arr[left++];
        } else {
            compare_count++;
            temp[i++] = arr[right++];
        }
    }

    while (left <= mid) {
        swap_count++;
        temp[i++] = arr[left++];
    }

    while (right <= high) {
        swap_count++;
        temp[i++] = arr[right++];
    }

    for (int j = low; j <= high; j++) {
        arr[j] = temp[j - low];
    }
}

void mergeSort(int arr[], int low, int high) {
    if (low >= high) return;
    int mid = (low + high) >> 1;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    mergeFunc(arr, low, mid, high);
}

void quickSort(int arr[], int low, int high) {
    if (low >= high) return;
    int pivot = arr[low];
    int left = low;
    int right = high;

    while (left < right) {
        while (left < high && arr[left] <= pivot){
            left++;
            compare_count++;
        }
        while (right > low &&  arr[right] > pivot){
            right--;
            compare_count++;
        }
        if (left < right) {
            swap(arr[left], arr[right]);
            swap_count++;
        }
    }

    swap(arr[low], arr[right]);
    swap_count++;
    quickSort(arr, low, right - 1);
    quickSort(arr, right + 1, high);
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        compare_count++;
        largest = left;
    }
    if (right < n &&  arr[right] > arr[largest]) {
        largest = right;
        compare_count++;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);
        swap_count++;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        swap_count++;
        heapify(arr, i, 0);
    }
}


int median(vector<int>& v) {
    sort(v.begin(), v.end());
    int n = v.size();
    if (n == 0) return 0.0;
    if (n % 2 == 0) {
        return (v[n/2 - 1] + v[n/2]) / 2.0;
    } else {
        return v[n/2];
    }
}


int main() {
    const int ARRAY_SIZE = 1000;
    const int TESTS = 500;
    srand(static_cast<unsigned>(time(0)));

    
    vector<int> bubble_swaps, bubble_comparisons;
    vector<int> bubble_times;

    vector<int> insertion_swaps, insertion_comparisons;
    vector<int> insertion_times;

    vector<int> selection_swaps, selection_comparisons;
    vector<int> selection_times;

    vector<int> merge_swaps, merge_comparisons;
    vector<int> merge_times;

    vector<int> quick_swaps, quick_comparisons;
    vector<int> quick_times;

    vector<int> heap_swaps, heap_comparisons;
    vector<int> heap_times;

    for (int i = 0; i < TESTS; i++) {
        int base[ARRAY_SIZE];
        generator(base, ARRAY_SIZE);

        //Bubble Sort
        {
            int arr_copy[ARRAY_SIZE];
            copy(base, base + ARRAY_SIZE, arr_copy);
            swap_count = 0;
            compare_count = 0;

            auto start = high_resolution_clock::now();
            bubbleSort(arr_copy, ARRAY_SIZE);
            auto end = high_resolution_clock::now();
            int duration = duration_cast<microseconds>(end - start).count();

            bubble_swaps.push_back(swap_count);
            bubble_comparisons.push_back(compare_count);
            bubble_times.push_back(duration);
        }

        // Insertion Sort 
        {
            int arr_copy[ARRAY_SIZE];
            copy(base, base + ARRAY_SIZE, arr_copy);
            swap_count = 0;
            compare_count = 0;

            auto start = high_resolution_clock::now();
            insertionSort(arr_copy, ARRAY_SIZE);
            auto end = high_resolution_clock::now();
            int duration = duration_cast<microseconds>(end - start).count();

            insertion_swaps.push_back(swap_count);
            insertion_comparisons.push_back(compare_count);
            insertion_times.push_back(duration);
        }

        //  Selection Sort
        {
            int arr_copy[ARRAY_SIZE];
            copy(base, base + ARRAY_SIZE, arr_copy);
            swap_count = 0;
            compare_count = 0;

            auto start = high_resolution_clock::now();
            selectionSort(arr_copy, ARRAY_SIZE);
            auto end = high_resolution_clock::now();
            int duration = duration_cast<microseconds>(end - start).count();

            selection_swaps.push_back(swap_count);
            selection_comparisons.push_back(compare_count);
            selection_times.push_back(duration);
        }

        //Merge Sort
        {
            int arr_copy[ARRAY_SIZE];
            copy(base, base + ARRAY_SIZE, arr_copy);
            swap_count = 0;
            compare_count = 0;

            auto start = high_resolution_clock::now();
            mergeSort(arr_copy, 0, ARRAY_SIZE - 1);
            auto end = high_resolution_clock::now();
            int duration = duration_cast<microseconds>(end - start).count();

            merge_swaps.push_back(swap_count);
            merge_comparisons.push_back(compare_count);
            merge_times.push_back(duration);
        }

        //Quick Sort
        {
            int arr_copy[ARRAY_SIZE];
            copy(base, base + ARRAY_SIZE, arr_copy);
            swap_count = 0;
            compare_count = 0;

            auto start = high_resolution_clock::now();
            quickSort(arr_copy, 0, ARRAY_SIZE - 1);
            auto end = high_resolution_clock::now();
            int duration= duration_cast<microseconds>(end - start).count();

            quick_swaps.push_back(swap_count);
            quick_comparisons.push_back(compare_count);
            quick_times.push_back(duration);
        }

        //Heap Sort 
        {
            int arr_copy[ARRAY_SIZE];
            copy(base, base + ARRAY_SIZE, arr_copy);
            swap_count = 0;
            compare_count = 0;

            auto start = high_resolution_clock::now();
            heapSort(arr_copy, ARRAY_SIZE);
            auto end = high_resolution_clock::now();
            int duration = duration_cast<microseconds>(end - start).count();

            heap_swaps.push_back(swap_count);
            heap_comparisons.push_back(compare_count);
            heap_times.push_back(duration);
        }
    }

    
    int bubble_mswaps       = median(bubble_swaps);
    int bubble_mcomparisons = median(bubble_comparisons);
    int bubble_mtime        = median(bubble_times);

    int insertion_mswaps       = median(insertion_swaps);
    int insertion_mcomparisons = median(insertion_comparisons);
    int insertion_mtime        = median(insertion_times);

    int selection_mswaps       = median(selection_swaps);
    int selection_mcomparisons = median(selection_comparisons);
    int selection_mtime        = median(selection_times);

    int merge_mswaps       = median(merge_swaps);
    int merge_mcomparisons = median(merge_comparisons);
    int merge_mtime        = median(merge_times);

    int quick_mswaps       = median(quick_swaps);
    int quick_mcomparisons = median(quick_comparisons);
    int quick_mtime        = median(quick_times);

    int heap_mswaps       = median(heap_swaps);
    int heap_mcomparisons = median(heap_comparisons);
    int heap_mtime        = median(heap_times);

    // Output results to "metrics.csv"
    ofstream outfile("metrics.csv");
    outfile << "Algorithm,Median_Swaps,Median_Comparisons,Median_Time_s\n";
    outfile << "BubbleSort," << bubble_mswaps << "," << bubble_mcomparisons << "," << bubble_mtime << "\n";
    outfile.close();

    // Append other algorithms to the same CSV
    ofstream outfile_app("metrics.csv", ios::app);
    outfile_app << "InsertionSort," << insertion_mswaps << "," << insertion_mcomparisons << "," << insertion_mtime << "\n";
    outfile_app << "SelectionSort," << selection_mswaps << "," << selection_mcomparisons << "," << selection_mtime << "\n";
    outfile_app << "MergeSort," << merge_mswaps << "," << merge_mcomparisons << "," << merge_mtime << "\n";
    outfile_app << "QuickSort," << quick_mswaps << "," << quick_mcomparisons << "," << quick_mtime << "\n";
    outfile_app << "HeapSort," << heap_mswaps << "," << heap_mcomparisons << "," << heap_mtime << "\n";
    outfile_app.close();

    return 0;
}