#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

// Function to perform DFS for finding augmenting paths in the bipartite graph
// `u` is the current node in the left set, `bp` is the adjacency list of the bipartite graph
// `matchR` stores the current matches for the right set, and `seen` keeps track of visited nodes
bool bpm(int u, vector<vector<int>>& bp, vector<int>& matchR, vector<bool>& seen) {
    for (int v : bp[u]) {
        if (seen[v]) continue; // Skip already visited nodes
        seen[v] = true;

        // If the node is not matched or we can find an augmenting path
        if (matchR[v] < 0 || bpm(matchR[v], bp, matchR, seen)) {
            matchR[v] = u; // Match the current node
            return true;
        }
    }
    return false;
}

int main() {
    // Open input file
    ifstream fin("input/input.txt");
    if (!fin.is_open()) {
        cout << "Error: Could not open input file.\n";
        return 1;
    }

    // Read the two sets of nodes (U and V)
    vector<string> U, V;
    string line;

    // Read the first line for set U
    getline(fin, line);
    {
        istringstream iss(line);
        string u;
        while (iss >> u) U.push_back(u);
    }

    // Read the second line for set V
    getline(fin, line);
    {
        istringstream iss(line);
        string v;
        while (iss >> v) V.push_back(v);
    }

    int n = U.size(), m = V.size(); // Sizes of the two sets

    // Read the adjacency matrix and build the adjacency list for the bipartite graph
    vector<vector<int>> bp(n); // Adjacency list for the bipartite graph
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            fin >> x;
            if (x) bp[i].push_back(j); // Add edge if x == 1
        }
    }
    fin.close();

    // Start timing the bipartite matching algorithm
    auto t1 = chrono::high_resolution_clock::now();

    // Perform maximum bipartite matching
    vector<int> matchR(m, -1); // Stores matches for the right set
    int result = 0; // Count of matches
    for (int u = 0; u < n; u++) {
        vector<bool> seen(m, false); // Reset visited nodes for each DFS
        if (bpm(u, bp, matchR, seen)) result++;
    }

    auto t2 = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(t2 - t1).count();

    // Open output file
    ofstream fout("output/output.txt");
    if (!fout.is_open()) {
        cout << "Error: Could not open output file.\n";
        return 1;
    }

    // Write the matching results to the output file
    for (int v = 0; v < m; v++) {
        if (matchR[v] >= 0) {
            fout << U[matchR[v]] << "-" << V[v] << "\n";
        }
    }
    fout.close();

    // Print timing results to the console
    cout << "Bipartite match time (ms): " << ms << "\n";

    return 0;
}
