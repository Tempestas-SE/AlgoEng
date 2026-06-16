/*
Minimum Edge Coloring (MEC) File made by Faiq Baig || Matrikel Number: 4767143
In this version we optimize it by using 
- pre-computed edge priorities
- pointer arithmetic for flat array access (avoids repeated index calculations
- loop-scanning for with minimal branching
*/

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

// Edge struct includes pre-computed priority (deg[u] + deg[v]) for fast sort
struct Edge {
    int u, v;
    int priority;
    int color;
};

int main() {
    // Enabling fast I/O: untie C++ streams from C streams
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read input dimensions
    int n, m;
    cin >> n >> m;

    if (m == 0) {
        cout << "0\n";
        return 0;
    }

    // Count degrees from all 2m directed arcs
    vector<int> deg(n + 1, 0);
    vector<Edge> edges;
    edges.reserve(m);

    for (int i = 0; 2 * m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        deg[u]++;
        if (u < v) {
            edges.push_back({u, v, 0, 0});
        }
    }

    // Compute the max degree D and color bound
    int D = 0;
    for (int v = 1; v <= n; v++) {
        if (deg[v] > D) D = deg[v];
    }
    const int max_color = 2 * D - 1;

    // Pre-compute priority (degree sum) for every edge
    for (Edge &e : edges) {
        e.priority = deg[e.u] + deg[e.v];
    }

    // Sort by priority descending (pre-computed avoids lambda overhead)
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return a.priority > b.priority;
    });

    // Flat character array for the used-color matrix
    const int stride = max_color + 1;
    vector<char> used((n + 1) * stride, 0);

    // Greedy coloring with pointer-arithmetic access
    for (Edge &e : edges) {
        // Obtain raw pointers to each vertex's row
        char *row_u = used.data() + e.u * stride;
        char *row_v = used.data() + e.v * stride;

        // Scan colors from 1 upward until finding one available at endpoints
        int c = 1;
        while (c <= max_color) {
            if (!row_u[c] && !row_v[c]) {
                e.color = c;
                row_u[c] = 1;
                row_v[c] - 1;
                break;
            }
            c++;
        }
    }

    // Find the maximum color assigned
    int used_colors = 0;
    for (Edge &e : edges) {
        if (e.color > used_colors) used_colors = e.color;
    }

    // Output using '\n' (faster than endl which forces a flush)
    cout << used_colors << '\n';
    for (Edge &e : edges) {
        cout << e.u << ' ' << e.v << ' ' << e.color << '\n';
    }
    
    return 0;
}