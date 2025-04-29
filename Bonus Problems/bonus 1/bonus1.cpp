#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

// Function to build the last occurrence table for Boyer-Moore
vector<int> buildLast(const string& pat) {
    vector<int> last(27, -1); // Initialize all characters ('a'-'z' and ' ') to -1
    for (int i = 0; i < pat.size(); i++) {
        int index = (pat[i] == ' ') ? 26 : (pat[i] - 'a'); // Map 'a'-'z' to 0-25, ' ' to 26
        last[index] = i; // Store the last occurrence of each character
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
        int index = (txt[i + j] == ' ') ? 26 : (txt[i + j] - 'a'); // Map 'a'-'z' to 0-25, ' ' to 26
        i += max(1, j - last[index]); // Shift based on mismatch
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

    // Start timing the Boyer-Moore algorithm
    auto t1 = chrono::high_resolution_clock::now();
    int idx = boyer_moore(pat, txt);
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
    cout << "Boyer-Moore time (ms): " << ms << "\n";

    return 0;
}
