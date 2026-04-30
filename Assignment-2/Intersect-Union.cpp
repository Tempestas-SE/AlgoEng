#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // Adjacency list: neighbors only (weights not needed for neighborhood operations)
    vector<set<int>> adj(n + 1);

    for (int i = 0; i < 2 * m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].insert(v);  
        // set ensures that there are no duplicates automatically
    }

    int s, t;
    cin >> s >> t;

    // Intersection: Nodes that appear in BOTH neighbor sets
    vector<int> inter;
    for (int node : adj[s]) {
        if (adj[t].count(node))
            inter.push_back(node);
    }

    // Union: This will merge both sets while the duplicates are handled by set semantics
    set<int> unionSet(adj[s].begin(), adj[s].end());
    for (int node : adj[t])
        unionSet.insert(node);

    // Sets that are already sorted will be output directly
    for (int i = 0; i < (int)inter.size(); i++) {
        if (i) cout << " ";
        cout << inter[i];
    }
    cout << "\n";

    bool first = true;
    for (int node : unionSet) {
        if (!first) cout << " ";
        cout << node;
        first = false;
    }
    cout << "\n";

    return 0;
}