/*
Min-Edge-Coloring (MEC) File made by Faiq Baig || Matrikel Number : 4767143
This versison of MEC uses Naive Greedy - scans all the edges of both endpoints
for each candidate color.
*/

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Structure to store an undirected edge and its assigned color
struct Edge {
    int u, v;
    int color;
};

int main() {
    // Read number of vertices and edges
    int n, m;
    scanf("%d %d", &n, &m);

    // Handle empty graphs
    if (m == 0) {
        printf("0\n");
        return 0;
    }

    // Count degree from all 2m directed arcss and build adjacency lists
    vector<int> deg(n + 1, 0);
    vector<Edge> edges;
    edges.reserve(m);
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < 2 * m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        deg[u]++; // each directed arc contributes to degree

        // Keep each undirected edge only once (when u < v)
        if (u < v) {
            int idx = edges.size();
            edges.push_back({u, v, 0});
            adj[u].push_back(idx);
            adj[v].push_back(idx);
        }
    }

    // Find the maximum degree D
    int D = 0;
    for (int v = 1; v <= n; v++) {
        D = max(D, deg[v]);
    }
    int max_color = 2 * D - 1; // guaranteed upper bound

    // Greedy coloring: for each edge, try colors from 1 upward
    for (Edge &e : edges) {
        for (int c = 1; c <= max_color; c++) {
            bool used = false;

            // Check if any incident edge of u already uses color c
            for (int idx : adj[e.u]) {
                if (edges[idx].color == c) {
                    used = true;
                    break;
                }
            }
            if (used) continue;

            // Check if any incident edge of v already uses color c
            for (int idx : adj[e.v]) {
                if (edges[idx].color == c) {
                    used = true;
                    break;
                }
            }
            if (!used) {
                e.color = c;
                break;
            }
        }
    }

    // Determine the number of distinct colors used
    int used_colors = 0;
    for (Edge &e : edges) {
        used_colors = max(used_colors, e.color);
    }

    // Output: color count then each edge with its color
    printf("%d\n", used_colors);
    for (Edge &e : edges) {
        printf("%d %d %d\n", e.u, e.v, e.color);
    }
    
    return 0;
}