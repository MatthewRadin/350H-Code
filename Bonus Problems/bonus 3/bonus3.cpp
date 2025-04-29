#include <vector>
#include <fstream>
#include <chrono>
#include <iostream>

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
    vector<pair<int, double>> results; // Store results as (size, average time)

    // Test quick sort for different input sizes
    for (int sz : {10, 100, 1000, 10000, 100000}) {
        double sum = 0; // Sum of times for all trials

        // Perform 100 trials for each size
        for (int file = 1; file <= 100; file++) {
            // Construct the file name dynamically
            string fname = "input/input" + to_string(sz) + "_" + to_string(file) + ".txt";
            cout << "Processing file: " << fname << "\n"; // Debugging output

            ifstream fin(fname);
            if (!fin.is_open()) {
                cout << "Could not open input file " << fname << ".\n";
                continue; // Skip to the next file
            }

            // Read the input numbers into a vector
            vector<double> a(sz);
            for (int i = 0; i < sz; i++) fin >> a[i];
            fin.close();

            // Measure the time taken to sort the array
            auto t1 = chrono::high_resolution_clock::now();
            quick_sort(a, 0, a.size());
            auto t2 = chrono::high_resolution_clock::now();
            sum += chrono::duration<double, milli>(t2 - t1).count();
        }

        // Calculate the average time for this size
        results.push_back({sz, sum / 100.0});
    }

    // Write results to an output file
    ofstream fout("output/output.txt");
    if (!fout.is_open()) {
        cout << "Error: Could not open output file.\n";
        return 1;
    }

    fout << "Size,AvgTime(ms)\n"; // Write CSV header
    for (auto& p : results) {
        fout << p.first << "," << p.second << "\n"; // Write size and average time
    }
    fout.close();

    // Print results to the console
    cout << "Size,AvgTime(ms)\n";
    for (auto& p : results) {
        cout << p.first << "," << p.second << "\n";
    }

    return 0;
}
