// MWIS (Max Weight Independent Set) File made by Faiq Baig || Matrikel Nummer - 4767143

#include <cmath>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < 2 * m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<long long> weight(n + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &weight[i]);
    }

    // inSet[v] - Whethere v is currently in the independent set
    vector<bool> inSet(n + 1, false);
    vector<bool> active(n + 1, true);

    // -------- [1] Greedy construction by weight/degree ratio --------
    while (true) {
        int best = -1;
        double bestScore = -1.0;

        for (int v = 1; v <= n; v++) {
            if (!active[v]) continue;

            int activeDeg = 0;
            for (int u : adj[v]) {
                if (active[u]) activeDeg++;
            }

            double score = (double) weight[v] / activeDeg;
            if (score > bestScore) {
                bestScore = score;
                best = v;
            }
        }

        if (best == -1) break;

        inSet[best] = true;
        active[best] = false;
        for (int u : adj[best]) {
            active[u] = false;
          }
        }
        
        // -------- [2] Local Swap Improvement --------
        // For each vertex not in the set, we check if by swapping it in
        // Removing (its set-neighbors) gives a net weight gain
        bool improved = true;
        while (improved) {
            improved = false;

            for (int v = 1; v <= n; v++) {
                if (inSet[v]) continue;

                // Collecting set-neighbors of v
                long long neighborWeight = 0;
                vector<int> setNeighbors;
                for (int u : adj[v]) {
                    if (inSet[u]) {
                        neighborWeight += weight[u];
                        setNeighbors.push_back(u);
                    }
                }

                // Swapping is beneficial if v's weight exceedss all displaced neighbors
                if (weight[v] > neighborWeight) {
                    // Remove set-neighbors
                    for (int u : setNeighbors) {
                        inSet[u] = false;
                    }

                    // Adding v
                    inSet[v] = true;
                    improved = true;
                }
            }
        }

        // Collect result
        vector<int> result;
        long long totalWeight = 0;
        for (int v = 1; v <= n; v++) {
            if (inSet[v]) {
                result.push_back(v);
                totalWeight += weight[v];
            }
        }

        printf("%d\n", (int)result.size());
        printf("%lld\n", totalWeight);
        for (int i = 0; i < (int)result.size(); i++) {
            if (i > 0) printf(" ");
            printf("%d", result[i]);
        }
        printf ("\n");

        return 0;
    }