#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

// Function to heapify a subtree rooted at index `i` for a max-heap
// `n` is the size of the heap, and `H` is the heap array
// Sorts the new added element to the correct position in the heap by swapping it with its parent if it's larger
// and recursively heapifying the affected subtree
void heapify_max(vector<int>& H, int n, int i) {
    int largest = i, l = 2 * i, r = 2 * i + 1;
    if (l <= n && H[l] > H[largest])
        largest = l;
    if (r <= n && H[r] > H[largest])
        largest = r;
    if (largest != i) {
        swap(H[i], H[largest]);
        heapify_max(H, n, largest);
    }
}

// Function to heapify a subtree rooted at index `i` for a min-heap
// Sorts by swapping the new added element with its parent if it's smaller
void heapify_min(vector<int>& H, int n, int i) {
    int smallest = i, l = 2 * i, r = 2 * i + 1;
    if (l <= n && H[l] < H[smallest])
        smallest = l;
    if (r <= n && H[r] < H[smallest])
        smallest = r;
    if (smallest != i) {
        swap(H[i], H[smallest]);
        heapify_min(H, n, smallest);
    }
}

// These two are tests to check if the heap is valid
// They check if the heap property is maintained for all nodes in the heap
bool isMinHeap(const vector<int>& arr, int n) {
    for (int i = 0; i <= n; ++i) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l <= n && arr[i] > arr[l]) {
            return false;
        }
        if (r <= n && arr[i] > arr[r]) {
            return false;
        }
    }
    return true;
}

bool isMaxHeap(const vector<int>& arr, int n) {
    for (int i = 0; i <= n; ++i) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l <= n && arr[i] < arr[l]) {
            return false;
        }
        if (r <= n && arr[i] < arr[r]) {
            return false;
        }
    }
    return true;
}

int main() {
    ifstream fin("input/input.txt");
    if (!fin.is_open()) {
        cerr << "Could not open input file.\n";
        return 1;
    }

    // Read the number of elements
    int n;
    fin >> n;

    // Read the elements into a vector and sets the amount of keys to be n+1
    // The first element is unused to make the heap 1-indexed (-inf)
    vector<int> keys(n + 1);
    for (int i = 1; i <= n; i++)
        fin >> keys[i];
    fin.close();

    // Start timing and build max-heap
    auto H = keys; // Original keys
    auto t1 = chrono::high_resolution_clock::now();
    for (int i = n/2; i >= 1; i--)
        heapify_max(H, n, i);
    auto t2 = chrono::high_resolution_clock::now();
    double tmax = chrono::duration<double, milli>(t2 - t1).count();

    // TESTING
    cout << "Is this a valid maxheap? (1 for yes): " << isMaxHeap(H, n) << endl;

    // Write max-heap to output file
    ofstream fout("output/output.txt");
    if (!fout.is_open()) {
        cerr << "Could not open output file.\n";
        return 1;
    }
    fout << "Max-Heap:\n";
    for (int i = 1; i <= n; i++) fout << H[i] << " ";
    fout << "\n";

    // Start timing and build min-heap
    H = keys; // Reset keys
    t1 = chrono::high_resolution_clock::now();
    for (int i = n / 2; i >= 1; i--)
        heapify_min(H, n, i);
    t2 = chrono::high_resolution_clock::now();
    double tmin = chrono::duration<double, milli>(t2 - t1).count();

    // Write min-heap to output file
    fout << "Min-Heap:\n";
    for (int i = 1; i <= n; i++) fout << H[i] << " ";
    fout << "\n";
    fout.close();

    // TESTING  
    // Check if the min-heap is valid
    cout << "Is this a valid minheap? (1 for yes): ";
    cout << isMinHeap(H, n) << endl;
    // TESTING

    // Print timing results to console
    cout << "Max-Heap build time (ms): " << tmax << "\n";
    cout << "Min-Heap build time (ms): " << tmin << "\n";

    return 0;
}
