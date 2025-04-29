#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;

int main() {
    ifstream fin("input/input.txt");
    if (!fin.is_open()) {
        cout << "Could not open input file.\n";
        return 1;
    }

    // Read the number of nodes in the graph
    int n;
    fin >> n;

    // Read the adjacency matrix
    vector<vector<double>> D(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          string value;
          fin >> value;
          if (value == "INF") {
              D[i][j] = 1e9; // Use a large value to represent infinity
          } else {
              D[i][j] = stod(value); // Convert the string to a double
          }
        }
    }
    fin.close();

    // Start timing
    auto t1 = chrono::high_resolution_clock::now();

    // Floyd-Warshall algorithm to compute shortest paths
    // Initialize the distance matrix with the adjacency matrix, and set diagonal to 0
    // D[i][i] = 0 for all i
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }

    auto t2 = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(t2 - t1).count();

    ofstream fout("output/output.txt");
    if (!fout.is_open()) {
        cerr << "Error: Could not open output file.\n";
        return 1;
    }

    // Write the resulting shortest path matrix to the output file
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fout << D[i][j] << (j + 1 < n ? " " : "");
        }
        fout << "\n";
    }
    fout.close();

    // Print timing results to the console
    cout << "Floyd-Warshall time (ms): " << ms << "\n";

    return 0;
}
