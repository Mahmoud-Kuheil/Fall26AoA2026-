# Empirical Analysis of Sorting Algorithms

**Student:** Mahmoud Kuheil (SAP ID: 71597)[cite: 4]  
**Repository:** Fall26AoA2026-[cite: 6]

## Source Files
- `sorting_analysis.cpp` — Empirical timing benchmark for Bubble Sort, Selection Sort, Insertion Sort, and Merge Sort across sizes 5, 10, 50, and 100[cite: 4, 7].
- `sorting_metrics.cpp` — Execution time, comparisons, and swaps for Selection Sort, Bubble Sort, Quick Sort, and Merge Sort on sorted and reverse-sorted inputs[cite: 9].

## How to Compile and Run
```bash
g++ -O2 -std=c++17 sorting_analysis.cpp -o sorting_analysis
./sorting_analysis
