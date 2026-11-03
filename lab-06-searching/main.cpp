// Lab 06 - Linear search vs Binary search (with comparison counting)
#include <iomanip>
#include <iostream>
#include <vector>

int linearSearch(const std::vector<int>& a, int target, int& comparisons) {
    comparisons = 0;
    for (size_t i = 0; i < a.size(); i++) {
        comparisons++;
        if (a[i] == target) return static_cast<int>(i);
    }
    return -1;
}

int binarySearch(const std::vector<int>& a, int target, int& comparisons) {   // array must be sorted
    comparisons = 0;
    int low = 0, high = static_cast<int>(a.size()) - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        comparisons++;
        if (a[mid] == target) return mid;
        if (a[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int main() {
    std::vector<int> data;
    for (int i = 1; i <= 1000; i++) data.push_back(i * 3);     // 3, 6, 9, ..., 3000 (sorted)

    std::cout << "Array: 1000 sorted numbers (3, 6, 9, ..., 3000)\n\n";
    std::cout << "target | linear index | linear comps | binary index | binary comps\n";
    for (int target : {3, 1500, 2997, 3000, 1001}) {
        int lc, bc;
        int li = linearSearch(data, target, lc);
        int bi = binarySearch(data, target, bc);
        std::cout << std::setw(6) << target << " | " << std::setw(12) << li << " | " << std::setw(12) << lc << " | "
                  << std::setw(12) << bi << " | " << std::setw(12) << bc << '\n';
    }
    std::cout << "\nLinear search is O(n); binary search is O(log n) -> at most ~10 comparisons for 1000 items.\n";
    return 0;
}
