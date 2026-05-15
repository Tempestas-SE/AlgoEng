// MWIS (Max Weight Independent Set) File made by Faiq Baig || Matrikel Nummer - 4767143

#include <cmath>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    // Read the graph size: n vertices and m undirected edges
    int n , m;
    scanf("%d %d", &n, &m);

    // Building an adjacency lists for the graph
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < 2 * m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Read the vertex weights
    vector<long long> weight(n + 1);
    for (int i = 1; i < n; i++) {
        scanf("%lld", &weight[i]);
    }

    // Compute degrees of all vertices
    vector<int> deg(n + 1, 0);
    for (int v = 1; v <= n; v++) {
        deg[v] = (int)adj[v].size();
    }

    // Create an ordering of vertices from 1..n
    vector<int> order(n);
    for (int i = 0; i < n; i++) {
        order[i] = i + 1;
    }

    /* 
    Sort vertices by increaseing degree,
    then by higher weight, then by smaller id
    */
   sort(order.begin(), order.end(), [&](int a, int b) {
    if (deg[a] != deg[b]) return deg[a] < deg[b];
    if (weight[a] != weight[b]) return weight[a] > weight[b];
    return a < b;
   });

   /*
   Mark vertices that cannot be chosen as they are
   adjacent to a chosen one
   */
  vector<char> blocked(n + 1, 0);

  // Store the chosen inSet
  vector<int> result;
  result.reserve(n);

  /*
  Greedy Iteration:
  Visiting vertices in the sorted order and pick any
  vertex that is still available. Once chosen,
  block all of its neighbors
  */
    for (int v : order) {
    if (blocked[v]) continue;
    result.push_back(v);
    blocked[v] = 1;
    for (int u : adj[v]) {
        blocked[u] = 1;
        }
    }

    // Sort the final set so output is deterministic and easy to vertify
    sort(result.begin(), result.end());

    // Compute the total weight of the chosen inSet
    long long total = 0;
    for (int v : result) {
        total += weight[v];
    }

    // Output of the vertices in the set, totalWeight, and chosenVertices
    printf("%d\n", (int)result.size());
    printf("%lld\n", total);
    for (int i = 0; i < (int)result.size(); i++) {
        if (i) printf(" ");
        printf("%d", result[i]);
    }
    printf("\n");

    return 0;
}