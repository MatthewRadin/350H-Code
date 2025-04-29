#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// MergeSort
// Merge two sorted subarrays A[p..q] and A[q+1..r], inclusive
void Merge(vector<int>& A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    vector<int> L(n1 + 1), R(n2 + 1);

    // Copy left and right halves
    for (int i = 0; i < n1; ++i) L[i] = A[p + i];
    for (int j = 0; j < n2; ++j) R[j] = A[q + 1 + j];

    // Add large sentinel values
    L[n1] = 2147483647; // Use the maximum value of an int as the sentinel
    R[n2] = 2147483647;

    // Merge back into A[p..r]
    int i = 0, j = 0;
    for (int k = p; k <= r; ++k) {
        if (L[i] <= R[j]) {
            A[k] = L[i++];
        } else {
            A[k] = R[j++];
        }
    }
}

// Recursive Merge-Sort on A[p..r]
void MergeSort(vector<int>& A, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        Merge(A, p, q, r);
    }
}

// QuickSort
// Partition A[p..r] around pivot A[r], returns pivot index
int Partition(vector<int>& A, int p, int r) {
    int pivot = A[r];
    int i = p - 1;
    for (int j = p; j < r; ++j) {
        if (A[j] <= pivot) {
            ++i;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    int temp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = temp;
    return i + 1;
}

// Recursive Quick-Sort on A[p..r]
void QuickSort(vector<int>& A, int p, int r) {
    if (p < r) {
        int q = Partition(A, p, r);
        QuickSort(A, p, q - 1);
        QuickSort(A, q + 1, r);
    }
}

int main() {
    ifstream fin("input/input.txt");
    if (!fin.is_open()) {
        cout << "Error: Could not open input file.\n";
        return 1;
    }

    // Read input numbers into a vector
    vector<int> orig;
    int x;
    while (fin >> x) orig.push_back(x);
    fin.close();

    // Merge-Sort
    vector<int> A = orig; // Copy original array for Merge-Sort
    auto t1 = clock();
    if (!A.empty()) MergeSort(A, 0, static_cast<int>(A.size()) - 1);
    auto t2 = clock();
    double merge_sort_time = (t2 - t1) * 1000.0 / CLOCKS_PER_SEC;

    // Write Merge-Sort results to output file
    ofstream fout("output/output.txt");
    if (!fout.is_open()) {
        cout << "Error: Could not open output file.\n";
        return 1;
    }
    fout << "Merge-Sort:\n";
    for (int v : A) fout << v << " ";
    fout << "\n";

    // Quick-Sort
    A = orig; // Reset array for Quick-Sort
    t1 = clock();
    if (!A.empty()) QuickSort(A, 0, static_cast<int>(A.size()) - 1);
    t2 = clock();
    double quick_sort_time = (t2 - t1) * 1000.0 / CLOCKS_PER_SEC;

    // Write Quick-Sort results to output file
    fout << "Quick-Sort:\n";
    for (int v : A) fout << v << " ";
    fout << "\n";
    fout.close();

    // Print timing results to console
    cout << "Merge-Sort time (ms): " << merge_sort_time << "\n";
    cout << "Quick-Sort time (ms): " << quick_sort_time << "\n";

    return 0;
}
