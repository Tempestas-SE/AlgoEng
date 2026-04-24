#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <map>           // needed for map
#include <utility>       // for pair; sometimes included by default, but safe to add
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    // We will store each unique undirected edge: (min(u,v), max(u,v)) -> weight
    map<pair<int, int>, int> edgeWeight;

    // Read all 2m directed arcs
    for (int i = 0; i < 2 * m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        // Normalize the edge so that u <= v
        if (u > v) {
            swap(u, v);
        }

        // Store (or overwrite) the weight for this edge
        edgeWeight[make_pair(u, v)] = w;
    }

    // Read the block of each node (nodes are 1..n)
    vector<int> block(n + 1);
    vector<int> blockSize(k, 0);  // blockSize[i] = number of nodes in block i

    for (int i = 1; i <= n; i++) {
        cin >> block[i];
        blockSize[block[i]]++;
    }

    int edgeCut = 0;
    long long weightedEdgeCut = 0;

    // Iterate over each unique edge once
    for (const auto& p : edgeWeight) {
        int u = p.first.first;
        int v = p.first.second;
        int w = p.second;

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
