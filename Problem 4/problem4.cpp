#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

// Function to implement Horspool's string matching algorithm
// `pat` is the pattern to search for, and `txt` is the text to search in
// Returns the starting index of the first occurrence of `pat` in `txt`, or -1 if not found
int horspool(const string& pat, const string& txt) {
    int m = pat.size(); // Length of the pattern
    int n = txt.size(); // Length of the text

    // Build the shift table for lowercase alphabet letters (only length 26)
    vector<int> shift(26, m); // Initialize all shifts to the length of the pattern
    for (int i = 0; i < m - 1; i++) {
        shift[pat[i] - 'a'] = m - 1 - i; // Set shift values based on the pattern
    }

    // Search for the pattern in the text
    int i = 0; // Start index in the text
    while (i <= n - m) {
        int j = m - 1; // Start comparing from the end of the pattern
        while (j >= 0 && pat[j] == txt[i + j]) j--; // Compare characters from right to left
        if (j < 0) return i; // Pattern found at index `i`
        i += shift[txt[i + m - 1] - 'a']; // Shift based on the mismatch character
    }

    return -1; // Pattern not found
}

int main() {
    // Open input file
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

    // Start timing the Horspool algorithm
    auto t1 = chrono::high_resolution_clock::now();
    int idx = horspool(pat, txt);
    auto t2 = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(t2 - t1).count();

    // Open output file
    ofstream fout("output/output.txt");
    if (!fout.is_open()) {
        cout << "Could not open output file.\n";
        return 1;
    }

    // Write the result to the output file
    fout << idx << "\n"; // Write the index of the first occurrence, or -1 if not found
    fout.close();

    // Print timing results to the console
    cout << "Horspool time (ms): " << ms << "\n";

    return 0;
}
