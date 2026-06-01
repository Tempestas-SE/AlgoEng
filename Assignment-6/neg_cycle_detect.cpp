// Matriculation Number: 4767143 | Negative Cycle Detection file made by Faiq Baig

// Bellman-Ford method: Detects Negative Cycle and reconstructs it via predecessor array

#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

const long long INF = 1e18;

struct Edge {int u, v, w; };

//  Initialize-Single-Source (G, s);
/*
    Setting all distances to 0 (equivalent to virtual nodes -> all)
    Ensuring all negative cycles are reachable regardless of graph connectivity
*/
void initSingleSource(int n, std::vector<long long>& d, std::vector<int>& pred) {
    d.assign(n + 1, INF);
    pred.assign(n + 1, -1);
    for (int i = 1; i <= n; i++) d[i] = 0;
}

//  Relax(u, v, w):
/*
    If a shorter path to v is found through u, update d[v] and record predecessor
    Return true if relaxation occured (distance was improved)
*/
bool relax(int u, int v, int w, std::vector<long long>& d, std::vector<int>& pred) {
    if (d[u] != INF && d[v] > d[u] + (long long)w) {
        d[v] = d[u] + (long long)w;
        pred[v] = u;
        return true;
    }
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    // Read all edges into edge list
    std::vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
        std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
    
    std::vector<long long> d;
    std::vector<int> pred;

    // Initialize-Single-Source (G, s)
    initSingleSource(n, d, pred);

    /*
    Bellman-Ford(G, w, s):
    Run n iterations instead of n-1
    This way it both relaxes and detects any negative cycle
    (Last relaxed node is recorded as the entry point into the negative cycle)
    */
    int last = -1;
    for (int i = 1; i <= n; i++) {
        last = -1;
        // For each edge (u, v) in E: Relax(u, v, w)
        for (auto& e : edges)
            if (relax(e.u, e.v, e.w, d, pred))
                last = e.v;
    }

    // If no relaxation occured in the nth pass, no negative cycle exists
    if (last == -1) {
        std::cout << 0 << "\n";
        return 0;
    }

    /*
    Walk back n steps along predecessors to guarantee we land
    inside the cycle (not the path leading to it)
    */
    int x = last;
    for (int i = 1; i <= n; i++) x = pred[x];

    // Trace the cycle from x back to x using predecessor pointers
    std::vector<int> cycle;
    int cur = x;
    do {
        cycle.push_back(cur);
        cur = pred[cur];
    } while (cur != x);
    cycle.push_back(x); // Repeats the first node to close the cycle

    // Reverse so the cycle reads in forward traversal order
    std::reverse(cycle.begin(), cycle.end());

    // Output: number of nodes in cycle, then the cycle with first node repeated
    std::cout << (int)cycle.size() - 1 << "\n";
    for (int node : cycle) std::cout << node << " ";
    std::cout << "\n";

    return 0;
}