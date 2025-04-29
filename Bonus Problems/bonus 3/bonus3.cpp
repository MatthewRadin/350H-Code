#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

// Function to perform quick sort
void quick_sort(vector<double>& a, int l, int r) {
    if (r - l <= 1) return; // Base case: single element
    double pivot = a[r - 1]; // Choose the last element as the pivot
    int i = l;
    for (int j = l; j < r - 1; j++) {
        if (a[j] < pivot) swap(a[i++], a[j]);
    }
    swap(a[i], a[r - 1]);
    quick_sort(a, l, i);
    quick_sort(a, i + 1, r);
}

int main() {
    vector<pair<int, double>> results;

    // Test quick sort for different input sizes
    for (int sz : {10, 100, 1000, 10000, 100000}) {
        double sum = 0;

        // Perform 100 trials for each size
        for (int file = 1; file <= 100; file++) {
            string fname = "input/input" + to_string(sz) + "_" + to_string(file) + ".txt";
            ifstream fin(fname);
            if (!fin.is_open()) {
                cout << "Could not open input file " << fname << ".\n";
                return 1;
            }

            vector<double> a(sz);
            for (int i = 0; i < sz; i++) fin >> a[i];
            fin.close();

            auto t1 = chrono::high_resolution_clock::now();
            quick_sort(a, 0, a.size());
            auto t2 = chrono::high_resolution_clock::now();
            sum += chrono::duration<double, milli>(t2 - t1).count();
        }

        results.push_back({sz, sum / 100.0}); // Store average time
    }

    // Print results as CSV for external plotting
    cout << "Size,AvgTime(ms)\n";
    for (auto& p : results) {
        cout << p.first << "," << p.second << "\n";
    }

    return 0;
}
