#include<algorithm>
#include<chrono>
#include<iostream>
#include<string>
#include<vector>
using namespace std;
using Clock = chrono::high_resolution_clock;
 
long long comparisons = 0;
long long swapsCount = 0;
 
void selectionSort(vector<int>&a) {
    int n = (int)a.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            ++comparisons;
            if (a[j] < a[minIndex]) minIndex = j;
        }
        if (minIndex != i) {
            swap(a[i], a[minIndex]);
            ++swapsCount;
        }
    }
}
 
void bubbleSort(vector<int>&a) {
    int n = (int)a.size();
    for (int i = 0; i < n - 1; ++i) {
        bool changed = false;
        for (int j = 0; j < n - i - 1; ++j) {
            ++comparisons;
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                ++swapsCount;
                changed = true;
            }
        }
        if (!changed) break;
    }
}
 
int partitionArray(vector<int>&a, int low, int high) {
    int pivot = a[high]; // Last element is the pivot.
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        ++comparisons;
        if (a[j] <= pivot) {
            ++i;
            if (i != j) {
                swap(a[i], a[j]);
                ++swapsCount;
            }
        }
    }
    if (i + 1 != high) {
        swap(a[i + 1], a[high]);
        ++swapsCount;
    }
    return i + 1;
}
 
void quickSort(vector<int>&a, int low, int high) {
    if (low < high) {
        int pivotIndex = partitionArray(a, low, high);
        quickSort(a, low, pivotIndex - 1);
        quickSort(a, pivotIndex + 1, high);
    }
}
 
void mergeParts(vector<int>&a, int left, int mid, int right) {
    vector<int> L(a.begin() + left, a.begin() + mid + 1);
    vector<int> R(a.begin() + mid + 1, a.begin() + right + 1);
    int i = 0, j = 0, k = left;
    while (i < (int)L.size() && j < (int)R.size()) {
        ++comparisons;
        if (L[i] <= R[j]) a[k++] = L[i++];
        else a[k++] = R[j++];
    }
    while (i < (int)L.size()) a[k++] = L[i++];
    while (j < (int)R.size()) a[k++] = R[j++];
}
 
void mergeSort(vector<int>&a, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);
        mergeParts(a, left, mid, right);
    }
}
 
void runSort(const string&algorithm, vector<int>&a) {
    if (algorithm == "Selection Sort") selectionSort(a);
    else if (algorithm == "Bubble Sort") bubbleSort(a);
    else if (algorithm == "Quick Sort") {
        if (!a.empty()) quickSort(a, 0, (int)a.size() - 1);
    } else if (algorithm == "Merge Sort") {
        if (!a.empty()) mergeSort(a, 0, (int)a.size() - 1);
    }
}
 
int main() {
    const int sizes[] = {5, 5, 100, 100};
    const string orders[] = {"Sorted", "Reverse Sorted", "Sorted", "Reverse Sorted"};
    const int trials = 3;
    const int repetitions = 20000;
 
    cout << "Algorithm,Input,Average_microseconds,Comparisons,Swaps\n";
    for (const string algorithm : {"Selection Sort", "Bubble Sort", "Quick Sort", "Merge Sort"}) {
        for (int test = 0; test < 4; ++test) {
            int n = sizes[test];
            vector<int> original(n);
            for (int i = 0; i < n; ++i) {
                original[i] = (orders[test] == "Sorted") ? i + 1 : n - i;
            }
 
            double totalMicroseconds = 0.0;
            long long totalComparisons = 0;
            long long totalSwaps = 0;
 
            for (int trial = 0; trial < trials; ++trial) {
                long long trialComparisons = 0;
                long long trialSwaps = 0;
                auto start = Clock::now();
                for (int r = 0; r < repetitions; ++r) {
                    vector<int> values = original;
                    comparisons = 0;
                    swapsCount = 0;
                    runSort(algorithm, values);
                    trialComparisons += comparisons;
                    trialSwaps += swapsCount;
                }
                auto finish = Clock::now();
                totalMicroseconds += chrono::duration<double, micro>(finish - start).count() / repetitions;
                totalComparisons += trialComparisons / repetitions;
                totalSwaps += trialSwaps / repetitions;
            }
 
            double averageTime = totalMicroseconds / trials;
            cout << algorithm << "," << n << " " << orders[test] << ","
                 << averageTime << "," << totalComparisons / trials << ","
                 << totalSwaps / trials << "\n";
        }
    }
    return 0;
}
