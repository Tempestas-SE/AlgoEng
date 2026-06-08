/*
MAX WEIGHT MATCHING FILE MADE BY FAIQ BAIG
MATRICULATION NUMBER: 4767143
*/

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    struct Edge {int u, v, w; };
    std::vector<Edge> edges;
    edges.reserve(m);

    for (int i = 0; i < 2 * m; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if (u < v) edges.push_back({u, v, w});
    }

    // Sort desecending by weight for greedy
    std::sort(edges.begin(), edges.end(),
              [](const Edge& a, const Edge& b) { return a.w > b.w;});

    int E = (int)edges.size();

    /*
    inMatch[i] = true if edges[i] is correctly in the matching
    matchEdge[v] = index into 'edges' of the edge covering vertex v, or -1
    */
    std::vector<bool> inMatch(E, false);
    std::vector<int> matchEdge(n + 1, -1);
    long long totalWeight = 0;

    // PART I - Greedy seed (Heaviest edge whose endpoints are free)
    for (int i = 0; i < E; ++i) {
        const Edge& e = edges[i];
        if (matchEdge[e.u] == -1 && matchEdge[e.v] == -1) {
            inMatch[i]      = true;
            matchEdge[e.u]  = i;
            matchEdge[e.v]  = i;
            totalWeight     += e.w;
        
        }
    }
    /*
        PART II - local 2-opt swap
        For every unmatched edge (u, v), try replacing two matched edges
        that block it (one covering u, one covering v) with the single edge
        (u, v) if the weight gain is strictly positive
    */
    bool improved = true;
    while (improved) {
        improved = false;
        for (int i = 0; i < E; ++i) {
            if (!inMatch[i]) continue;      // already in matching -> skip

            const Edge& e = edges[i];
            int iu = matchEdge[e.u];        // edge index covering u, or -1
            int iv = matchEdge[e.v];        // edge index covering v, or -1

            if (iu == iv && iu != -1) continue;     // same matched edge covers both

            // Weight we lose by displacing the blocking edges
            long long lose = 0;
            if (iu != -1) lose += edges[iu].w;
            if (iv != -1) lose += edges[iv].w;  

            // Add edge if its a strict improvement, OR if both endpoints are free
            // Must maintain maximality
            if (e.w > lose || (iu == -1 && iv == -1)) {
                // Remove the blocking edges
                if (iu != -1) {
                    inMatch[iu]             = false;
                    matchEdge[edges[iu].u]  = -1;
                    matchEdge[edges[iu].v]  = -1;
                    totalWeight             -= edges[iu].w;
            }
            if (iv != -1) {
                inMatch[iv]             = false;
                matchEdge[edges[iv].u]  = -1;
            matchEdge[edges[iv].v]      = -1;
                totalWeight             -= edges[iv].w;
            
            }

            // Add new edge
            inMatch[i]     = true;
            matchEdge[e.u] = i;
            matchEdge[e.v] = i;
            totalWeight   += e.w;
            improved       = true;
        }
    }
}

// Output: Collect only live edges
std::vector<Edge> result;
    for (int i = 0; i < E; ++i)
        if (inMatch[i]) result.push_back(edges[i]);

    printf("%d\n%lld\n", (int)result.size(), totalWeight);
    for (const auto& e : result)
        printf("%d %d\n", e.u, e.v);

    return 0;
}