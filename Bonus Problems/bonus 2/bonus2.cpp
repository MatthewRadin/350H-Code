#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

// Function to heapify a subtree rooted at index `i`
void heapify(vector<int>& H, int n, int i) {
    int largest = i, l = 2 * i, r = 2 * i + 1;
    if (l <= n && H[l] > H[largest]) largest = l;
    if (r <= n && H[r] > H[largest]) largest = r;
    if (largest != i) {
        swap(H[i], H[largest]);
        heapify(H, n, largest);
    }
}

int main() {
    ifstream fin("input/input.txt");
    if (!fin.is_open()) {
        cout << "Could not open input file.\n";
        return 1;
    }

    // Read the number of elements
    int n;
    fin >> n;
    vector<int> H(n + 1);
    for (int i = 1; i <= n; i++) fin >> H[i];
    fin.close();

    // Start timing the heap sort algorithm
    auto t1 = chrono::high_resolution_clock::now();

    // Build max-heap
    for (int i = n / 2; i >= 1; i--) heapify(H, n, i);

    // Perform heap sort
    vector<int> sorted;
    for (int sz = n; sz >= 1; sz--) {
        sorted.push_back(H[1]);
        swap(H[1], H[sz]);
        heapify(H, sz - 1, 1);
    }

    auto t2 = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(t2 - t1).count();

    ofstream fout("output/output.txt");
    if (!fout.is_open()) {
        cout << "Could not open output file.\n";
        return 1;
    }

    // Write the heap and sorted results to the output file
    fout << "Heap after build:\n";
    for (int i = 1; i <= n; i++) fout << H[i] << " ";
    fout << "\nSorted (descending):\n";
    for (int v : sorted) fout << v << " ";
    fout << "\n";
    fout.close();

    // Print timing results to the console
    cout << "Heap sort time (ms): " << ms << "\n";

    return 0;
}
