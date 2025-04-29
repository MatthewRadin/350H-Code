

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <chrono>

using namespace std;

// This function checks if the graph is connected using BFS
// It starts from node 0 and marks all reachable nodes as visited using a queue
// If all nodes are visited, it returns true; otherwise, it returns false
bool isConnected(const vector<vector<bool>>& A, int n) {
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(0);
    visited[0] = true;

    while (!q.empty()) { 
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++) {
            if (A[u][v] && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    // Extra check for if all nodes are visited
    for (bool v : visited) {
        if (!v) return false;
    }
    return true;
}

int main() {
    // Open input file
    ifstream fin("input/input.txt");
    if (!fin.is_open()) {
        cout << "Could not open input file.\n";
        return 1;
    }
    int n;
    fin >> n;
    vector<vector<bool>> A(n, vector<bool>(n));

    // Read adjacency matrix and validate that it is square and binary (correctly formatted)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            if (!(fin >> x) || (x != 0 && x != 1)) {
                cout << "Invalid adjacency matrix.\n";
                return 1;
            }
            A[i][j] = x;
        }
    }
    fin.close();

    // Start timing
    auto t1 = chrono::high_resolution_clock::now();

    // For all nodes, the degree is the number of edges connected to it, which is the sum of the row in the adjacency matrix
    // So the degree of node [i] is the sum of A[i][j] for all j from 0 to n-1

    // Check for FullConnectedMesh
    // A fully connected mesh is a complete graph where every node is connected to every other node
    // This means that the degree of each node should be n-1
    // if any pair of nodes, i and j, are not connected (A[i][j] == 0), then the graph is not a mesh
    bool isMesh = true;
    vector<int> deg(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j]) deg[i]++;
            if (i != j && !A[i][j]) isMesh = false;
        }
    }

    // Check for star topology
    // A star topology has one center node connected to all other nodes, which are not connected to each other
    // This means that the degree of the center node should be n-1, and all other nodes should have a degree of 1
    // If any node has a degree other than 1 or n-1 (), then the graph is not a star topology
    bool isStar = false;
    int centers = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i] == n - 1) centers++;
        else if (deg[i] != 1) centers = -100;
    }
    if (centers == 1) isStar = true;

    // Check for ring topology
    // A ring topology has each node connected to two other nodes, forming a closed loop
    // This means that the degree of each node should be 2 exactly.
    bool isRing = true;
    if (isConnected(A, n)) {
        for (int d : deg) {
            if (d != 2) isRing = false;
        }
    } else {
        isRing = false;
    }

    // End timing and compute elapsed time
    auto t2 = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(t2 - t1).count();

    // Open output file
    ofstream fout("output/output.txt");
    if (!fout.is_open()) {
        cout << "Could not open output file.\n";
        return 1;
    }

    // Results:
    if (isMesh) fout << "fully connected mesh\n";
    else if (isStar) fout << "star\n";
    else if (isRing) fout << "ring\n";
    else fout << "none\n";
    fout.close();
    cout << "Topology check time (ms): " << ms << "\n";
    return 0;
}
