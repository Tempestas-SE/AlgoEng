#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    // We will store each unique undirected edge as (u, v, w)
    // We will read all 2m directed arcs, but only keep one copy of each edge
    vector<int> edge_u(m);
    vector<int> edge_v(m);
    vector<int> edge_w(m);

    // Keep a seen flag for each edge index (just for input reading simplicity)
    vector<bool> seenEdge(m, false);

    // Read all 2m directed arcs
    for (int i = 0; i < 2 * m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        // Normalize: always store with u <= v
        if (u > v) {
            swap(u, v);
        }

        // Find the edge index; assume edges are numbered 0..m-1
        // Here we just trust that the input gives m distinct edges
        // We will mark the first occurrence we see for each edge
        bool found = false;
        for (int idx = 0; idx < m; idx++) {
            if (edge_u[idx] == 0 && !seenEdge[idx]) {
                // First time storing this edge slot
                edge_u[idx] = u;
                edge_v[idx] = v;
                edge_w[idx] = w;
                seenEdge[idx] = true;
                found = true;
                break;
            }
            // If the slot already has this edge, we don’t need to store again
            else if (edge_u[idx] == u && edge_v[idx] == v) {
                found = true;
                break;
            }
        }
        // If we reach here, either it was already stored or we stored it above
    }

    // Read the block of each node (nodes are 1..n)
    vector<int> block(n + 1);
    vector<int> blockSize(k, 0);

    for (int i = 1; i <= n; i++) {
        cin >> block[i];
        blockSize[block[i]]++;
    }

    int edgeCut = 0;
    long long weightedEdgeCut = 0;

    // Iterate over all m unique edges
    for (int i = 0; i < m; i++) {
        int u = edge_u[i];
        int v = edge_v[i];
        int w = edge_w[i];

        if (block[u] != block[v]) {
            edgeCut++;
            weightedEdgeCut += w;
        }
    }

    // Find the size of the heaviest block
    int heaviest = 0;
    for (int i = 0; i < k; i++) {
        heaviest = max(heaviest, blockSize[i]);
    }

    // Balance = (size of heaviest block) / (n / k)
    double balance = (double)heaviest / ((double)n / (double)k);

    cout << edgeCut << '\n';
    cout << weightedEdgeCut << '\n';
    cout << balance << '\n';

    return 0;
}
