#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

// Function to build the last occurrence table for Boyer-Moore
vector<int> buildLast(const string& pat) {
    vector<int> last(256, -1); // Initialize all characters to -1
    for (int i = 0; i < pat.size(); i++) {
        last[(unsigned char)pat[i]] = i; // Store the last occurrence of each character
    }
    return last;
}

// Function to perform Boyer-Moore string matching
int boyer_moore(const string& pat, const string& txt) {
    int m = pat.size(), n = txt.size();
    auto last = buildLast(pat); // Build the last occurrence table
    int i = 0;

    while (i <= n - m) {
        int j = m - 1;
        while (j >= 0 && pat[j] == txt[i + j]) j--; // Compare characters from right to left
        if (j < 0) return i; // Pattern found at index `i`
        i += max(1, j - last[(unsigned char)txt[i + j]]); // Shift based on mismatch
    }
    return -1; // Pattern not found
}

int main() {
    ifstream fin("input/input.txt");
    if (!fin.is_open()) {
        cout << "Could not open input file.\n";
        return 1;
    }

    // Read the pattern and text from the input file
    string pat, txt;
    getline(fin, pat); // First line is the pattern
    getline(fin, txt); // Second line is the text
    fin.close();

    // Start timing the Boyer-Moore algorithm
    auto t1 = chrono::high_resolution_clock::now();
    int idx = boyer_moore(pat, txt);
    auto t2 = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(t2 - t1).count();

    ofstream fout("output/output.txt");
    if (!fout.is_open()) {
        cout << "Could not open output file.\n";
        return 1;
    }

    // Write the result to the output file
    fout << idx << "\n"; // Write the index of the first occurrence, or -1 if not found
    fout.close();

    // Print timing results to the console
    cout << "Boyer-Moore time (ms): " << ms << "\n";

    return 0;
}
