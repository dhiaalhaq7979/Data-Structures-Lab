// Lab 07 - Sorting algorithms: bubble, selection, insertion and merge sort
// each sort counts its comparisons so we can compare them
#include <iostream>
#include <vector>

using Vec = std::vector<int>;

long long bubbleSort(Vec& a) {
    long long comps = 0;
    for (size_t i = 0; i + 1 < a.size(); i++) {
        bool swapped = false;
        for (size_t j = 0; j + 1 < a.size() - i; j++) {
            comps++;
            if (a[j] > a[j + 1]) { std::swap(a[j], a[j + 1]); swapped = true; }
        }
        if (!swapped) break;   // already sorted -> best case O(n)
    }
    return comps;
}

long long selectionSort(Vec& a) {
    long long comps = 0;
    for (size_t i = 0; i + 1 < a.size(); i++) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < a.size(); j++) {
            comps++;
            if (a[j] < a[minIndex]) minIndex = j;
        }
        std::swap(a[i], a[minIndex]);
    }
    return comps;
}

long long insertionSort(Vec& a) {
    long long comps = 0;
    for (size_t i = 1; i < a.size(); i++) {
        int key = a[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0) {
            comps++;
            if (a[j] <= key) break;
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
    return comps;
}

void merge(Vec& a, int left, int mid, int right, long long& comps) {
    Vec temp;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right) {
        comps++;
        temp.push_back(a[i] <= a[j] ? a[i++] : a[j++]);
    }
    while (i <= mid) temp.push_back(a[i++]);
    while (j <= right) temp.push_back(a[j++]);
    for (size_t k = 0; k < temp.size(); k++) a[left + k] = temp[k];
}

void mergeSortRec(Vec& a, int left, int right, long long& comps) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortRec(a, left, mid, comps);
    mergeSortRec(a, mid + 1, right, comps);
    merge(a, left, mid, right, comps);
}

long long mergeSort(Vec& a) {
    long long comps = 0;
    mergeSortRec(a, 0, static_cast<int>(a.size()) - 1, comps);
    return comps;
}

void print(const Vec& a) {
    for (int x : a) std::cout << x << ' ';
    std::cout << '\n';
}

bool isSorted(const Vec& a) {
    for (size_t i = 1; i < a.size(); i++) if (a[i - 1] > a[i]) return false;
    return true;
}

int main() {
    const Vec original = {64, 25, 12, 22, 11, 90, 3, 47};
    std::cout << "Input: "; print(original);

    struct Algo { const char* name; long long (*fn)(Vec&); };
    Algo algos[] = {{"Bubble sort   ", bubbleSort}, {"Selection sort", selectionSort},
                    {"Insertion sort", insertionSort}, {"Merge sort    ", mergeSort}};

    for (const Algo& al : algos) {
        Vec a = original;
        long long comps = al.fn(a);
        std::cout << al.name << ": "; print(a);
        std::cout << "                comparisons = " << comps << (isSorted(a) ? "  [sorted]" : "  [ERROR]") << '\n';
    }

    std::cout << "\nComparisons on 1000 numbers in reverse order (worst case for simple sorts):\n";
    Vec big;
    for (int i = 1000; i >= 1; i--) big.push_back(i);
    for (const Algo& al : algos) {
        Vec a = big;
        std::cout << "  " << al.name << " -> " << al.fn(a) << '\n';
    }
    return 0;
}
