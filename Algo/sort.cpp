#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

int swap_count = 0;
int compare_count = 0;

// Generate random array values
void generator(int arr[], int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 50000 + 1;
}

// Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j <= i - 1; j++) {
            compare_count++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swap_count++;
            }
        }
    }
}

// Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            swap(arr[j + 1], arr[j]);
            swap_count++;
            compare_count++;
            j--;
        }
        arr[j + 1] = key;
    }
}

// Selection Sort
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

// Merge components
void mergeFunc(int arr[], int low, int mid, int high) {
    int left = low, right = mid + 1, i = 0;
    int temp[high - low + 1];
    while (left <= mid && right <= high) {
        swap_count++;
        compare_count++;
        if (arr[left] <= arr[right]) temp[i++] = arr[left++];
        else temp[i++] = arr[right++];
    }
    while (left <= mid) {
        swap_count++;
        temp[i++] = arr[left++];
    }
    while (right <= high) {
        swap_count++;
        temp[i++] = arr[right++];
    }
    for (int j = low; j <= high; j++)
        arr[j] = temp[j - low];
}

// Merge Sort
void mergeSort(int arr[], int low, int high) {
    if (low >= high) return;
    int mid = (low + high) >> 1;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    mergeFunc(arr, low, mid, high);
}

// Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low >= high) return;
    int pivot = arr[low], left = low, right = high;
    while (left < right) {
        while (left < high && arr[left] <= pivot) {
            compare_count++;
            left++;
        }
        while (right > low && arr[right] > pivot) {
            compare_count++;
            right--;
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

// Heapify for Heap Sort
void heapify(int arr[], int n, int i) {
    int largest = i, left = 2*i + 1, right = 2*i + 2;
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
        compare_count++;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
        compare_count++;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        swap_count++;
        heapify(arr, n, largest);
    }
}

// Heap Sort
void heapSort(int arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        swap_count++;
        heapify(arr, i, 0);
    }
}

// Find median
int median(vector<int>& v) {
    sort(v.begin(), v.end());
    int n = v.size();
    if (n == 0) return 0;
    if (n % 2 == 0) return (v[n/2 - 1] + v[n/2]) / 2;
    else return v[n/2];
}

int main() {
    srand((unsigned) time(0));

    // Varying sizes
    vector<int> sizes = {100,500,1000,1500,2000,2500,3000,3500,4000,4500,5000};
    // Prepare new CSV for all sizes
    ofstream outfile("metrics_varying.csv");
    outfile << "Algorithm,Input_Size,Median_Swaps,Median_Comparisons,Median_Time_microseconds\n";
    outfile.close();

    // Number of repeated tests per size
    const int TESTS = 250;

    // Collect stats for each size
    for (auto size : sizes) {
        vector<int> bubble_swaps, bubble_comparisons, bubble_times;
        vector<int> insertion_swaps, insertion_comparisons, insertion_times;
        vector<int> selection_swaps, selection_comparisons, selection_times;
        vector<int> merge_swaps, merge_comparisons, merge_times;
        vector<int> quick_swaps, quick_comparisons, quick_times;
        vector<int> heap_swaps, heap_comparisons, heap_times;

        for (int t = 0; t < TESTS; t++) {
            vector<int> base(size);
            for (int i = 0; i < size; i++)
                base[i] = rand() % 50000 + 1;

            // Bubble Sort
            {
                vector<int> arr_copy = base;
                swap_count = 0; compare_count = 0;
                auto start = high_resolution_clock::now();
                bubbleSort(arr_copy.data(), size);
                auto end = high_resolution_clock::now();
                bubble_swaps.push_back(swap_count);
                bubble_comparisons.push_back(compare_count);
                bubble_times.push_back((int)duration_cast<microseconds>(end - start).count());
            }

            // Insertion Sort
            {
                vector<int> arr_copy = base;
                swap_count = 0; compare_count = 0;
                auto start = high_resolution_clock::now();
                insertionSort(arr_copy.data(), size);
                auto end = high_resolution_clock::now();
                insertion_swaps.push_back(swap_count);
                insertion_comparisons.push_back(compare_count);
                insertion_times.push_back((int)duration_cast<microseconds>(end - start).count());
            }

            // Selection Sort
            {
                vector<int> arr_copy = base;
                swap_count = 0; compare_count = 0;
                auto start = high_resolution_clock::now();
                selectionSort(arr_copy.data(), size);
                auto end = high_resolution_clock::now();
                selection_swaps.push_back(swap_count);
                selection_comparisons.push_back(compare_count);
                selection_times.push_back((int)duration_cast<microseconds>(end - start).count());
            }

            // Merge Sort
            {
                vector<int> arr_copy = base;
                swap_count = 0; compare_count = 0;
                auto start = high_resolution_clock::now();
                mergeSort(arr_copy.data(), 0, size - 1);
                auto end = high_resolution_clock::now();
                merge_swaps.push_back(swap_count);
                merge_comparisons.push_back(compare_count);
                merge_times.push_back((int)duration_cast<microseconds>(end - start).count());
            }

            // Quick Sort
            {
                vector<int> arr_copy = base;
                swap_count = 0; compare_count = 0;
                auto start = high_resolution_clock::now();
                quickSort(arr_copy.data(), 0, size - 1);
                auto end = high_resolution_clock::now();
                quick_swaps.push_back(swap_count);
                quick_comparisons.push_back(compare_count);
                quick_times.push_back((int)duration_cast<microseconds>(end - start).count());
            }

            // Heap Sort
            {
                vector<int> arr_copy = base;
                swap_count = 0; compare_count = 0;
                auto start = high_resolution_clock::now();
                heapSort(arr_copy.data(), size);
                auto end = high_resolution_clock::now();
                heap_swaps.push_back(swap_count);
                heap_comparisons.push_back(compare_count);
                heap_times.push_back((int)duration_cast<microseconds>(end - start).count());
            }
        }

        // Compute medians
        int bs  = median(bubble_swaps);
        int bc  = median(bubble_comparisons);
        int bt  = median(bubble_times);

        int isw = median(insertion_swaps);
        int ic  = median(insertion_comparisons);
        int it  = median(insertion_times);

        int ss  = median(selection_swaps);
        int sc  = median(selection_comparisons);
        int st  = median(selection_times);

        int msw = median(merge_swaps);
        int mc  = median(merge_comparisons);
        int mt  = median(merge_times);

        int qs  = median(quick_swaps);
        int qc  = median(quick_comparisons);
        int qt  = median(quick_times);

        int hsw = median(heap_swaps);
        int hc  = median(heap_comparisons);
        int ht  = median(heap_times);

        // Write rows for each algorithm
        ofstream outfile_app("metrics_varying.csv", ios::app);
        outfile_app << "BubbleSort,"    << size << "," << bs  << "," << bc  << "," << bt  << "\n";
        outfile_app << "InsertionSort," << size << "," << isw << "," << ic  << "," << it  << "\n";
        outfile_app << "SelectionSort," << size << "," << ss  << "," << sc  << "," << st  << "\n";
        outfile_app << "MergeSort,"     << size << "," << msw << "," << mc  << "," << mt  << "\n";
        outfile_app << "QuickSort,"     << size << "," << qs  << "," << qc  << "," << qt  << "\n";
        outfile_app << "HeapSort,"      << size << "," << hsw << "," << hc  << "," << ht  << "\n";
        outfile_app.close();
    }
    return 0;
}