/* 
Contracting Cluster file made by Faiq Baig | Matrikel Number: 4767143
This version of Contracting Cluster uses a sort and a linear sweep.
That in turn allows for no hashing at all, a fully deterministic O(m log m)
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <map>

using namespace std;

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k); // n - nodes, m - undirected edges, k - clusters

    // Read all 2m directed arcs (u, v, w)
    int totalArcs = 2 * m;
    vector<int> arcU(totalArcs), arcV(totalArcs), arcW(totalArcs);
    for (int i = 0; i < totalArcs; i++) {
        scanf("%d %d %d", &arcU[i], &arcV[i], &arcW[i]);
    }

    // Read cluster key C(i) for every node, 1-indexed
    vector<int> key(n + 1);
    for (int i = 1; i <= n; i++) scanf("%d", &key[i]);

    // Big node weight (How many original nodes fall into that cluster)
    // Every original node has weight 1 - This just counts
    vector<long long> nodeWeight(k, 0);
    for (int i = 1; i <= n; i++) nodeWeight[key[i]]++;

    /*
    Aggregate arc weights between distinct clusters
    Map key = (soruceCluster, destCluster); both directions to be stored separately
    This ends up with equal weight automatically -> each undirected edge already
    appears as two opposite directed arcs in the input
    */
    map<pair<int, int>, long long> edgeWeight;
    for (int i = 0; i < totalArcs; i++) {
        int a = key[arcU[i]];
        int b = key[arcV[i]];
        if (a != b) edgeWeight[{a, b}] += arcW[i]; // Drops intra-cluster (now intra-node) arcs    
    }

    // Count each undirected big edge (a < b) to get M
    int M = 0;
    for (auto &e : edgeWeight) {
        if (e.first.first < e.first.second) M++;
    }
    
    printf("%d %d\n", k, M);

    // Print in both directions for every big edge
    for (auto &e : edgeWeight) {
        int a = e.first.first, b = e.first.second;
        if (a < b) {
            printf("%d %d %lld\n", a, b, e.second);
            printf("%d %d %lld\n", b, a, edgeWeight[{b, a}]);
        }
    }

    // Printing the big node weights, in order 0...k-1
    for (int c = 0; c < k; c++) printf("%lld\n", nodeWeight[c]);

    return 0;
}