#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
using namespace std;
using Clock = chrono::high_resolution_clock;

void bubbleSort(vector<int>& a) {
    int n = (int)a.size();
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (a[j] > a[j + 1])
                swap(a[j], a[j + 1]);
}

void selectionSort(vector<int>& a) {
    int n = (int)a.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j)
            if (a[j] < a[minIndex])
                minIndex = j;
        swap(a[i], a[minIndex]);
    }
}

void insertionSort(vector<int>& a) {
    for (int i = 1; i < (int)a.size(); ++i) {
        int key = a[i], j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            --j;
        }

        a[j + 1] = key;
    }
}

void mergeParts(vector<int>& a, int left, int mid, int right) {
    vector<int> L(a.begin() + left, a.begin() + mid + 1);
    vector<int> R(a.begin() + mid + 1, a.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < (int)L.size() && j < (int)R.size())
        a[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];

    while (i < (int)L.size())
        a[k++] = L[i++];

    while (j < (int)R.size())
        a[k++] = R[j++];
}

void mergeSortRec(vector<int>& a, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    mergeSortRec(a, left, mid);
    mergeSortRec(a, mid + 1, right);

    mergeParts(a, left, mid, right);
}

void mergeSort(vector<int>& a) {
    if (!a.empty())
        mergeSortRec(a, 0, (int)a.size() - 1);
}

int main() {
    const int sizes[] = {5, 10, 50, 100};
    const int repetitions = 5;
    const int iterations = 10000;

    cout << "Algorithm,N,Average_microseconds_per_sort\n";

    for (string name : {
        "Bubble Sort",
        "Selection Sort",
        "Insertion Sort",
        "Merge Sort"
    }) {
        for (int n : sizes) {
            vector<int> original(n);

            for (int i = 0; i < n; ++i)
                original[i] = n - i;

            double total = 0.0;

            for (int run = 0; run < repetitions; ++run) {
                auto start = Clock::now();

                for (int k = 0; k < iterations; ++k) {
                    vector<int> a = original;

                    if (name == "Bubble Sort")
                        bubbleSort(a);
                    else if (name == "Selection Sort")
                        selectionSort(a);
                    else if (name == "Insertion Sort")
                        insertionSort(a);
                    else
                        mergeSort(a);
                }

                auto finish = Clock::now();

                total += chrono::duration<double, micro>(
                    finish - start
                ).count() / iterations;
            }

            cout << name << "," << n << ","
                 << (total / repetitions) << "\n";
        }
    }

    return 0;
}
